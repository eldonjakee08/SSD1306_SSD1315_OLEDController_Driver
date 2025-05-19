/*
 * ssd1306_ssd1315.h
 *
 *  Created on: May 17, 2025
 *      Author: eldon
 */

#ifndef DRIVER_SSD1306_SSD1315_H_
#define DRIVER_SSD1306_SSD1315_H_

#include "stm32f446xx.h" 	//my self-made i2c and gpio library
#include <stddef.h>
#include <string.h>

/*
 * User defined OLED parameters
 */
#define WIDTH					128 	//input OLED width pixels
#define HEIGHT 					64		//input OLED height pixels
#define OLED_ADDR				0x3C	//input OLED device address
#define OLED_I2C_PORT			I2C1	//if using different I2C port, refer @I2C_base_addresses

#define OLED_BUFFER_SIZE 		( (WIDTH * HEIGHT) / 8 )



// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} OLED_COLOR;


/*
 * function prototypes of APIs
 */

//APIs for communication with OLED
void oled_WriteCommand(uint8_t commandByte);
void oled_WriteData(uint8_t *pBuffer, size_t bufferSize);

//APIs for drawing into the OLED
void oled_DrawPixel(uint8_t x, uint8_t y, OLED_COLOR color);
void oled_Fill(OLED_COLOR color);
void oled_UpdateScreen(void);

//Other APIs for OLED
void oled_init(void);
void oled_SetDisplayOn(const uint8_t ONorOff);
void oled_SetContrast(uint8_t contrast)	;

#endif /* DRIVER_SSD1306_SSD1315_H_ */
