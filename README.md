# yado (Pronounced Yah-Dew)
"Yet Another Door Opener" ... ESP8266 based Door Controller with JSON REST API and Secure Password ACL. Intened for Garage Doors and Electronic Gate "Buzzers".

## Features

1. Open hardware available in ./hardware
 1. PCB available for purchase at OSHPark: TBD
 2. Full BOM available with distributor list: TBD (See BOM in ./hardware for part list)
 3. Utilizes nodemcu dev board (It's minimal and just $10 on ebay)
 4. Supports both v0.9 and v1.0 nodemcu footprints.
1. Open source code available in ./src.
2. Completed Features:
 1. Digest based authentication (No clear text passwords) ... Done
 2. Support for DHCP & Static addresses ... Done
 3. JSON REST API to read door sensors ... Done
 4. Serve all javascript libaries locally ... DONE
3. In progress
 1. USB Interface to configure all settings ... In progress
 2. Web Admin Interface for configuration ... Not started
 3. JSON REST API to open/close door ... Not started
 4. ... And more!
4. Planned
 1. RFID Card support

## JSON REST

1. /json/sensors
 1. Return state of the sensors
2. /json/digest/new
 1. Generate a new server digest and associated time

## To build code

1. Install Arduino IDE (It's a horrible environment, but easiest to get going): http://arduino.cc
2. Install board support for the ESP8266: https://github.com/esp8266/Arduino
3. Install CH341 USB to TTL Bridge Drivers: http://www.electrodragon.com/w/CH341
4. Load the Yagdo code into the Arduino IDE
5. Change the settings in the "defaults" section of the YADO source code.
6. Compile and load the code into your nodemcu dev board. (Select the esp8266 from the boards menu).

###

1. Install Atmel Studio and Visual Micro. This is a better IDE than the Arduino IDE.

## To access admin interface (work in progress)

1. Provide power to Yado
2. The LED1 will light solid. During this period, hold down the "user_flash" button.
3. Onces you press the button, LED1 will turn off.
4. Within 5 seconds, LED2 will start blinking. Let go of "user_flash".
5. Connect to the Yado access point.
 1. SSID: yado_admin
 2. Password: yado_admin
6. Point your browser to http://192.168.4.1

Important Note: You will have 30 minutes to make your changes. After 30 minutes, Yado will return to the default operation.