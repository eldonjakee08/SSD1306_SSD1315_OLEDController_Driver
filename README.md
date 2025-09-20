# SSD1306/SSD1315 OLED Driver
SSD1306/SSD1315 driver ported for STM32WB5MMG MCU which will be used for my MotoHUD Project. Repo Link: https://github.com/eldonjakee08/MOTOHUD_Project

You can port this to your desired STM32 MCU by changing the HAL header file to your desired MCU. You will also need to change the I2C peripheral handle.

# Limitations
1. This driver is currently set-up for 128x64px OLED displays. If OLED screen resolution is bigger, change the OLED "WIDTH" and "HEIGHT" macro definition in the ssd1306_ssd1315.h header file. You'd also need to add/subtract elements in the OLED_screenBuffer to match your new OLED screen buffer size.

<img width="1174" height="237" alt="image" src="https://github.com/user-attachments/assets/fbd6b805-7d6e-439c-a6a1-36cbd84a2218" /><br>


2. This driver only supports I2C protcol to communicate with the OLED controller. Will add SPI communication functionality in the future. 

# How To Use the Driver
1. Add the ssd1306_ssd1315.h header file to your main.c to access the OLED functions.
<img width="702" height="110" alt="image" src="https://github.com/user-attachments/assets/37c9ef26-a520-401b-b3df-64a266ea50e5" /><br>


2. Before calling any OLED functions/commands, initialize the OLED first by calling oled_init();. 
<img width="675" height="450" alt="image" src="https://github.com/user-attachments/assets/852b56be-564e-4caa-b5a3-756aecd3b6f2" />


# OLED Functions
**1. oled_init()**

<img width="803" height="108" alt="image" src="https://github.com/user-attachments/assets/618ebbff-2373-450b-b91e-6c916535a8c0" /><br>

**2. oled_DrawPixel()**

<img width="866" height="197" alt="image" src="https://github.com/user-attachments/assets/3058c41d-fd20-43ed-b484-962f5a9ffd3b" /><br>

**3. oled_Fill()**
 
 <img width="822" height="145" alt="image" src="https://github.com/user-attachments/assets/324e3e49-3a98-4189-8868-4be359d594f7" /><br>

**4. oled_UpdateScreen()**

 <img width="808" height="123" alt="image" src="https://github.com/user-attachments/assets/88bff539-aa7a-4e74-93db-b3bbecc2e1af" /><br>

**5. oled_SetDisplayOn()**

<img width="664" height="152" alt="image" src="https://github.com/user-attachments/assets/3cbefd2c-85c3-4522-843b-d12d204d975b" /><br>

**6. oled_SetContrast()**

<img width="576" height="150" alt="image" src="https://github.com/user-attachments/assets/d3497067-b4b8-435d-87cf-5aff68440ec5" /><br>

**7. oled_drawBMP()**

<img width="1422" height="557" alt="image" src="https://github.com/user-attachments/assets/08f1e383-7ccd-4631-a17a-3ccbf9f9adfc" /><br>

**8. oled_clearGlyphRegion()**

<img width="1199" height="350" alt="image" src="https://github.com/user-attachments/assets/f4ed1a9f-1557-4b1f-a2b4-ec0ab887a852" /><br>

**9. oled_RenderGlyph()**

<img width="1606" height="336" alt="image" src="https://github.com/user-attachments/assets/17a9e8b0-ae07-465e-9813-8efcc2a1794a" /><br>

**10. oled_ClearGlyph()**

<img width="1001" height="149" alt="image" src="https://github.com/user-attachments/assets/39b047a6-4913-4bcb-bfd8-5e71d16a4b89" /><br>


