# ForJoe

I'm on mac so I apologize if there are differences in the instructions. 
To upload code to the Calico please follow the following steps:
Get Board Files:
1) Open Arduino IDE
2) go to Arduino/Preferences/Additional Board Manager urls
3) copy and Past "https://adafruit.github.io/arduino-board-index/package_adafruit_index.json" into the field (Without Quotes)
4) Go to Tools/Boards/Board Manager
5) install the "ADAFRUIT SAMD BOARDS" Ensure you are installing the Adafruit samd library and not the arduino one. 
6) Close the Arduino IDE

Replace the board files:
1) Navigate to the new board files:
Mac: user/library/arduino15/packages/adafruit/hardware/samd/(Version number)/
3) Backup the Version number folder somewhere safe incase of issues. 
2) Replace the (version number) file with one located in the git repo, this contains the proper changes to all the neccesary files for the board to run.

Burn Bootloader:
1) Open Atmel Studio
2) Connect to Calico with Atmel ICE
3) Set BootProt in "fuses" to 0 before programming board
4) Navigate to the boards folder we just installed 
Mac: user/library/arduino15/packages/adafruit/hardware/samd/(Version number)/Bootloaders/ItsybitsyM0
5) Burn the .bin file found in the folder on the chip
6) set the Bootprot fuse back to 8kb before proceeding. 

Uploading arduino sketch:
When uploading your arduino sketch please ensure the following settings:
Board/ItsyBitsyM0
Optimize/Small (-Os) (Standard)
USB Stack/Arduino
DEBUG/Off

youre now all set to use Arduino with your board!
I believe the steps to be very similar with Platform IO although I dont have much experience with that.

if you have any issues what so ever please feel free to call or text anytime,

Kevin Preller




