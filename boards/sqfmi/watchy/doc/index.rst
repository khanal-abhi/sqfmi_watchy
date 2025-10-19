Getting Started
Watchy Kit w/ Case Assembly
Watchy Kit with Case

Before You Begin make sure you review the instructions and inspect for any missing or damaged components.

Remove The Components Carefully as they are tightly packed for maximum protection. The display is made of glass and will crack if you bend it!

Insert & Remove The Battery Carefully to avoid damaging PCB components

Test Your PCB to make sure the board is functional!

Do Not Apply The Included Tape!! Watchy can be assembled and secured with the included enclosure, without needing any tape. Only apply the tape if you intend to use Watchy without the enclosure, and have triple checked the screen is properly aligned.

Connect the screen to the FPC connector: the ribbon cable goes through the PCB slot, as in the image above; the shiny gold pins on the ribbon cable must face up; pull the black tabs out slightly before inserting the cable, then push the tabs back in after to secure cable.
Connect the battery
Connect the USB to start charging the battery
Press SW1 to bring up the menu/confirm
Press SW3 & SW4 to navigate up/down
Press SW2 to exit/cancel
Watchy Buttons

Wait 1 minute to check and see if the clock is updating the time correctly
Assembly Video: https://www.youtube.com/watch?v=ftLTrr_HTpI

Assembly Video (CNC Aluminum Case): https://www.youtube.com/watch?v=rbVr9eVb72M

Tips

Make sure the screen is perfectly aligned before taping it down! It should not extend above or below the strap holes on the PCB.
Watchy Screen Alignment

Make sure the battery cable is tucked in when assemblign the case. Everything should fit snug and be aligned to the bottom case, before securing the top case.
Do NOT force the case to close. It could break the screen & buttons! The case should close easily with the top and bottom snaps latching.
Do NOT overtighten the screws in the aluminum case Overtightening will crack the screen! Make sure everything fits nicely and slowly adjust the screws to secure the case.
Still having trouble? Check out this step-by-step guide on assembling the case in our FAQ
Arduino Setup
Watchy comes pre-loaded with firmware that demonstrates all the basic features. You can also try different watch faces and examples in Arduino.

Download and install the latest Arduino IDE

Start Arduino and open File > Preferences.

Under Additional Board Manager URLs add:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Open Tools > Board > Boards Manager and install the latest version of esp32 by Espressif Systems. Check to make sure you did not install Arduino ESP32 Boards by mistake.

Under Sketch > Include Library > Manage Libraries, search for Watchy and install the latest version

Make sure all the dependencies are installed i.e. GxEPD2 , WiFiManager, rtc_pcf8563,etc.

Enter Bootloader Mode
To upload new firmware/watchfaces to Watchy, you will need to enter bootloader mode
Plug in the USB on Watchy
Press and hold the top 2 buttons (Back & Up) for more than 4 seconds, then release the Back button first, before releasing the Up button
You should now see an ESP32S3 device enumerate a serial port i.e. COM, cu.*