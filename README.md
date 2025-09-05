# SSD1306_SSD1315_OLEDcontroller_Driver
Improved version from the previous version OLED driver. 

This driver is specifically ported for STM32WB5MMG MCU which will be used for my Motorcycle Helmet Hud Project Repo Link: 

You can port this to your desired STM32 MCU by changing the HAL header file to your desired MCU. You will also need to change the I2C peripheral handle.<br>

Integrates new functionalities to allow for glyph rendering and animation:
1. oled_drawBMP: Renders a monochrome bitmap glyph to the OLED screen at specified (x,y) coordinate.

2. oled_clearGlyphRegion: Clears the retangular region that a glyph occupies in the OLED.

3. oled_RenderGlyph: Renders a glyph to the OLED screen using the glyph metadata structure.<br>
   
*NOTE*
1. This driver is currently set-up for 128x64px OLED displays. You will need to port this to your desired OLED screen resolution by changing the OLED "WIDTH" and "HEIGHT" in the ssd1306_ssd1315.h header file. You'd also need to add/subtract elements in the OLED_screenBuffer to match your OLED screen resolution.

2. This driver only supports I2C protcol to communicate with the OLED controller.
   
3. To use the driver, add the ssd1306_ssd1315.h header file to your main.c to access the OLED functions.
<img width="702" height="110" alt="image" src="https://github.com/user-attachments/assets/37c9ef26-a520-401b-b3df-64a266ea50e5" />


4. Before calling any OLED functions/commands, initialize the OLED first by calling oled_init();. 
<img width="675" height="450" alt="image" src="https://github.com/user-attachments/assets/852b56be-564e-4caa-b5a3-756aecd3b6f2" />
