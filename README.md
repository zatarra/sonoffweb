# Sonoff wifi smart switch

This is a dirt cheap wifi enabled switch that you can use to turn on  all sorts of devices connected to mains AC.  Feel free to google it if you still have doubts.

- http://lmgtfy.com/?q=sonoff

# Ok, so what is this repo about?

This is a custom firmware that replaces the original one and provides you with a very simple  interface to turn on/off the relay. It gives you four endpoints:

- / `gets the current status of the relay`
- /enable `enable the relay`
- /disable `disable the relay`
- /toggle `toggle the relay on/off`

## Installation

Please refer to this wonderful tutorial on how to upload firmware to the sonoff switch:
`http://captain-slow.dk/2016/05/22/replacing-the-itead-sonoff-firmware/`

TL;DR: You need to solder a pin header to access the VCC/GND/RX/TX pins and then you can use the esptool or the arduino IDE to push the code by pressing the reset button while connecting it to power.

After installing the pin headers and ARDUINO IDE, all you have to do is to edit the ssid and password fields inside the sketch to match your network. Compile it and upload to the sonoff wifi switch.


##### DO NOT CONNECT THE SONOFF TO MAINS WHILE INTERFACING IT WITH YOUR COMPUTER JUST TO BE ON THE SAFE SIDE.

