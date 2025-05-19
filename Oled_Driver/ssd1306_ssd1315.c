
/**********************!!!!!!READ ME!!!!!!********************************
 * This is my take on SSD1306/SSD1315 OLED driver for STM32F4 processors
 * Everything is made from scratch, no STM32 HAL used
 * The I2C driver used on this library is my personal driver that I've developed (Bare Metal)
 * This is a testing ground to see if my I2C library works in real world applications
 * I took inspiration from Afiskon's STM32 SSD1306 OLED driver when developing this
 * But his version uses STM32 I2C HAL github link: https://github.com/afiskon/stm32-ssd1306

 ***********************!!!!LIMITATIONS!!!!*************************************
 * 1. This only works for STM32F4 series MCUs. I specifically developed this for NUCLEO F44RE
 * 2. This is limited only to 128x64 pixel screens. Will add more screen size options in the future
 * 3. This is only compatible with I2C communication SSD1306/SSD1315 OLED modules.
 * 4. For now it only has basic functionality like fill_screen and draw_pixel but I will be adding more functionality in the future.
 */


#include "ssd1306_ssd1315.h"

//screen buffer
static uint8_t OLED_ScreenBuffer[OLED_BUFFER_SIZE];

void delay(void) {

	for(uint32_t i=0; i < 100000; i++);
}

//sends out a 1 byte command to OLED display
void oled_WriteCommand(uint8_t commandByte) {
	/*
	 * This function does the following
	 * 1. initiates start phase and address phase.
	 * 2. send outs the control byte command "0x00" which means command stream (incoming stream of commands).
	 *	  We could also use the value "0x80" for a single command byte but "0x00" works fine.
	 * 3. It then send the single byte command inside the variable "commandByte"
	 * 4. generates STOP condition after sending because of "I2C_REPEATED_START_DI"
	 */
	I2C_MasterSendDataOLED(OLED_I2C_PORT, 0x00, &commandByte, 1, OLED_ADDR, I2C_REPEATED_START_DI);
}


//writes data into GDDRAM
void oled_WriteData(uint8_t *pBuffer, size_t bufferSize) {
	I2C_MasterSendDataOLED(OLED_I2C_PORT, 0x40, pBuffer, bufferSize, OLED_ADDR, I2C_REPEATED_START_DI);
}




void oled_init(void) {

	uint8_t startline = 0;

	//Sets display to OFF for initialization
	oled_SetDisplayOn(OFF);
	delay();


	oled_WriteCommand(0x20); //set memory addressing mode
	oled_WriteCommand(0x00); //set to horizontal addressing mode

	oled_WriteCommand(0xC8); //Set COM output scan direction, 0xC8 = top to bottom, 0xC0 = bottom to top (inverted)

	oled_WriteCommand(0x00); //Set column address lower nibble in page addressing mode
	oled_WriteCommand(0x10); //Set column address higher nibble in page addressing mode
							 //This commands basically sets Column 0 = 0x00 to be the starting column in page addressing mode

	oled_WriteCommand(0x40 | startline); //Set start line address, startline values 0 t 63.

	oled_SetContrast(0xFF);

	oled_WriteCommand(0xA1); //No horizontal mirroring, 0XA1 = no horizontal mirroring, col 0 to col 127
	//0xA0 = horizontal mirroring, col 127 to col 0

	oled_WriteCommand(0xA6); //Set normal color, 0xA6 = normal color, 0xA7 = inverted color display

	//Set multiplex ratio A.K.A number of rows to display on screen
	oled_WriteCommand(0xA8); //peripheral register address of set multiplex command
	oled_WriteCommand(0x3F); //0x3F = 63 dec, meaning rows 0 to rows 63 are displayed on the screen

	oled_WriteCommand(0xA4); //Normal operation, 0xA4 = output follow RAM content
	//0xA5 = output does not follow RAM content. Turns ON all pixels irregardless of RAM content

	//Set display offset
	oled_WriteCommand(0xD3); //peripheral register address of display offset command
	oled_WriteCommand(0x00); //0x00 = 0, means no vertical display offset; 0x3F = 63 max value vertical display offset
	//If there is vertical offset, the display is shifted up by n rows according to programmed offset value.

	//Sets oscillator freq & display clock divide ratio
	oled_WriteCommand(0xD5); //peripheral register address of oscillator freq/display clock divide
	oled_WriteCommand(0xF0); //0xF0 means F = 1111b/15dec, highest nibble which sets the oscillator frequency in Hz
	//0xF0 mean 0 = divide ratio values 0 to 15, both setting determine the Frame Freq (Hz)= Fosc / (D + 1) / 128

	oled_WriteCommand(0xD9); //command for setting the pre-charge period
	oled_WriteCommand(0x22); //each nibble corresponds to phase 2 Most Sig Nibble & phase 1 Least Sig Nibble. Duration is in DCLK cycles
	//default setting is 2 DCLK cycles or 0x22.

	oled_WriteCommand(0xDA); //COM pins hardware config, NOTE: in datasheet Bit 4 should be Bit 5 and Bit 5 should be bit 4. Baliktad in data sheet. PISTE!
	oled_WriteCommand(0x12); //0x12 = 0001 0010, Bit 5 = 0, Sequential COM pin config; Bit 4 = 1, COM pin left/right remap ; Bit 1 = 1 (reset value 0x2)

	oled_WriteCommand(0xDB); //set VCOMH voltage level, VCOMH is the COM pin voltage level when its idle state (not pulled to GND)
	oled_WriteCommand(0x20); //0x20, 0.77xVcc, at Vcc 3.3V estimate OLED voltage drop is only at 0.759V
	//which is lower than OLED threshold voltage of ~1.3V

	oled_WriteCommand(0x8D); //charge pump setting command
	oled_WriteCommand(0x14); //enable charge pump command
	oled_SetDisplayOn(ON); 	 //turn on OLED panel

	oled_Fill(Black);

	oled_UpdateScreen();
}




//draw a pixel on OLED screen.
void oled_DrawPixel(uint8_t x, uint8_t y, OLED_COLOR color) {

	if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		// Don't write outside the buffer
		return;
	}

	// Draw in the right color
	if(color == White) {
		//set the pixel (turn on the pixel)
		OLED_ScreenBuffer[x + (y / 8) * WIDTH] |= 1 << (y % 8);
	} else {
		//color is Black (turn off the pixel)
		OLED_ScreenBuffer[x + (y / 8) * WIDTH] &= ~(1 << (y % 8));
	}
}


/* Fill the whole screen with the given color */
void oled_Fill(OLED_COLOR color) {
	memset(OLED_ScreenBuffer, (color == Black) ? 0x00 : 0xFF, sizeof(OLED_ScreenBuffer));
}

//Writes data into RAM which is then displayed into the OLED
void oled_UpdateScreen(void) {

	for(uint8_t i = 0; i < HEIGHT/8; i++) {

		/*
		 * in Afiskon's library, he sets the page addressing mode into Horizontal
		 * But during screen update, he treats it like in page addressing mode.
		 * By adding lines of code that increments the page address every after each page write which is redundant see below code
		 * **********code*********
		 * oled_WrtieCommand(0XB0 + i);
		 * oled_WriteCommand(0x00);
		 * oled_WriteCommand(0x10);
		 * We are not in page addressing mode, we are in horizontal addressing mode, which is not needed since after writing
		 * to page 0 it automatically increments to page 1. I don't know the reason why he did it this way?
		 * Probably just to make sure that the pointer increments to the next page.
		 */

		oled_WriteData(&OLED_ScreenBuffer[WIDTH*i],WIDTH);
	}
}



void oled_SetDisplayOn(const uint8_t ONorOff) {

	if(ONorOff == ON){
		oled_WriteCommand(0xAF);	//OLED ON command
	}
	else{
		oled_WriteCommand(0xAE);	//OLED OFF command
	}
}

void oled_SetContrast(uint8_t contrast)	{
	oled_WriteCommand(0x81);
	oled_WriteCommand(contrast);
}















