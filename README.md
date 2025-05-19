# STM32_ssd1306_ssd1315_OLED_Driver
From Scratch STM32F4 ssd1306 &amp; ssd1315 OLED Driver (no HAL)

This is my take on SSD1306/SSD1315 OLED driver for STM32F4 processors
Everything is made from scratch, no STM32 HAL used. 
The I2C driver used on this library is my personal driver that I've developed (Bare Metal).
This is a testing ground to see if my I2C library works in real world applications.
I took inspiration from Afiskon's STM32 SSD1306 OLED driver when developing this.
But his version uses STM32 I2C HAL github link: https://github.com/afiskon/stm32-ssd1306.

***********************!!!!LIMITATIONS!!!!*************************************
1. This only works for STM32F4 series MCUs. I specifically developed this for NUCLEO F44RE
2. This is limited only to 128x64 pixel screens. Will add more screen size options in the future
3. This is only compatible with I2C communication SSD1306/SSD1315 OLED modules. 
4. For now it only has basic functionality like fill_screen and draw_pixel but I will be adding more functionality in the future.
 
