# yado (Pronounced Yah-Dew)
"Yet Another Door Opener" ... ESP8266 based Door Controller with JSON REST API and Secure Password ACL. Intened for Garage Doors and Electronic Gate "Buzzers".

## Features

1. Open hardware available in ./hardware
 1. PCB available for purchase at OSHPark
  1. https://www.oshpark.com/shared_projects/0cBHd21f
 2. Full BOM available with distributor list.
  1. (See BOM in ./hardware for part list)
 3. Utilizes nodemcu dev board (It's minimal and just $10 on ebay)
 4. Supports both v0.9 and v1.0 nodemcu footprints. 
   1. http://www.aliexpress.com/wholesale?shipCountry=us&shipFromCountry=&shipCompanies=&SearchText=nodemcu&exception=&minPrice=&maxPrice=&minQuantity=&maxQuantity=&isFreeShip=n&isFavorite=n&isRtl=yes&isOnSale=n&isBigSale=n&similar_style=n&similar_style_id=&isAtmOnline=n&CatId=0&g=y&SortType=total_tranpro_desc&initiative_id=SB_20150717073819&isPremium=y&filterCat=400103%2C515%2C4099&needQuery=n&groupsort=1
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
3. Install  USB to TTL Bridge Drivers
 1. CH341 : http://www.electrodragon.com/w/CH341 (older nodemcu)
 2. CP2102 : .... (newer nodemcu)
4. Load the Yagdo code into the Arduino IDE
5. Change the settings in the "defaults" section of the YADO source code.
6. Compile and load the code into your nodemcu dev board. (Select the esp8266 from the boards menu).

### Optional

1. Install Atmel Studio and Visual Micro. This is a better IDE than the Arduino IDE.

## Usage: Admin interface

1. Provide power to Yado
2. The LED1 will light solid for a few seconds. During this period, hold down the "user_flash" button.
3. Onces you press the button, LED1 will turn off.
4. When LED2 blinks. Let go of "user_flash".
5. Connect to the Yado access point.
 1. SSID: yado_admin
 2. Password: yado_admin
6. Point your browser to http://192.168.4.1
7. If this is your first time, select the "Load Defaults" link from main menu.

LED2 will continue to blink while Yado is in admin mode. Because unsecured networks are a bad idea, we have conciously decided not to support unsecured Access Points and they won't be listed in the WiFi configuration. Adding support will be a 3 line change, but let's not do it.

Using static IP addresses is recommended, but DHCP also works. The assigned DHCP address is available through the USB serial console (115200, 8n1), through your home router's interface or you can scan the network for Yado.

Important Note: You will have 30 minutes to make your changes. After 30 minutes, Yado will return to the default operation.

## Usage: Normal Interface

1. Point your web browser to Yado's IP address.
2. Type your access password and click 'open'.

## Usage: Installation

1. Connect the terminal labled "Open1" to your garage door opener.
2. Install an optional door sensor to "Sens1".

Sens2 is only exposed to the REST API. Open2 is not used. Adding supoprt for both will take some minimal effort, but the UI will need to be kept simple.