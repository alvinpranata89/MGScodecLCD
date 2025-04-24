# MGScodecLCD
This is a fun project showcasing conversation in the style of Metal Gear Solid franchise codec



https://github.com/user-attachments/assets/bcaa21e9-44ab-4eff-85ea-686e615afcf8

Im using ESP32 involving ESP32 and LCD screen (ILI9341) from mcufriend, and arduino IDE 2.3.2
first, you need to install the MCUFRIEND_kbv library from arduino IDE, then follow this wiring

Wiring mapping:
-------------------
LCD    ||    ESP32

D2    ---  GPIO 26

D3    ---  GPIO 25

D4    ---  GPIO 17/tx2

D5    --- GPIO 16/rx2

D6    ---  GPIO 27

D7    ---  GPIO 14

D0    ---  GPIO 12

D1    ---  GPIO 13

RST   ---  GPIO 32

CS    ---  GPIO 33

DC/RS ---  GPIO 15

WR    ---  GPIO 4

RD    ---  GPIO 2

the code is using UTFT library to create the pixels, I draw almost everything manually using primitive pixel drawing function including the dynamic voice meter and frequency digit (140.85), except for the incoming "CALL", Snake's and Colonel's face, those 3 are converted from png file into array.

One thing to note is, the MCUFriend library needs to be adjusted so it can be used on esp32, after line 1025 of 
<your_arduino_libraries_folder>/MCUFRIEND_kbv/utility/mcufriend_shield
add this line:
#include "hal/gpio_ll.h"

this is to avoid compilation error on arduino IDE



