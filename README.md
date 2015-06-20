# yado (Pronounced Yah-Dew)
"Yet Another  Door Opener" ... ESP8266 based Door Controller with JSON REST API and Secure Password ACL.

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
4. In progress
 1. USB Interface to configure all settings ... In progress
 2. Web Admin Interface for configuration ... Not started
 3. JSON REST API to open/close door ... Not started
 3. ... And more!

## To build code:

1. Install Arduino IDE (It's a horrible environment, but the best for ESP8266): http://arduino.cc
2. Install board support for the ESP8266: https://github.com/esp8266/Arduino
3. Install CH341 USB to TTL Bridge Drivers: http://www.electrodragon.com/w/CH341
4. Load the Yagdo code into the Arduino IDE
5. Change the settings in the "Settings" section of the YADO source code.
6. Compile and load the code into your nodemcu dev board.
