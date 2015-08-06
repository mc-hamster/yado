

/*
 * Copyright (c) 2015, Jm Casler
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * * Neither the name of Jm Casler nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Hash.h>

#include <EEPROM.h>
#include "EEPROMAnything.h"

// Configuration Start
const uint8_t numberOfUsers = 5;
const uint8_t passwordLength = 16;
const uint8_t noteLength = 32;

const uint8_t sensorLabelLength = 16;

// Contact sensors
struct csensor_t
{
  boolean enabled;
  boolean invert;
  char name[sensorLabelLength + 1]; // One more byte than required; String needs to be null terminated
  char high[sensorLabelLength + 1];  // Reserved
  char low[sensorLabelLength + 1];  // One more byte than required; String needs to be null terminated
};

//
struct access_t
{
  uint8_t admin;  // Reserved
  uint8_t conf;   // Reserved
  char password[passwordLength + 1]; // One more byte than required; String needs to be null terminated
  char user[passwordLength + 1];  // Reserved
  char note[noteLength + 1];  // One more byte than required; String needs to be null terminated
};

// This structure should not grow larger than 1024 bytes.
struct settings_t
{
  int initialized;       // If not "1", then we have not yet initialized with defaults
  char ssid[33];         // One more byte than required; String needs to be null terminated
  char ssidPassword[65]; // One more byte than required; String needs to be null terminated
  access_t accessGeneral[numberOfUsers];
  csensor_t contactSensors[2];
  uint8_t ipMode; // 0 = Dynamic, 1 = Static
  uint8_t ipAddress[4]; // 255.255.255.255
  uint8_t ipGateway[4]; // 255.255.255.255
  uint8_t ipSubnet[4];  // 255.255.255.255
} settings;

int requestTTL = 120;

// Configuration End

const byte DNS_PORT = 53;
ESP8266WebServer server ( 80 );
DNSServer dnsServer;

// Pin Assignment
const int ledHTTP = 0;     // Toggled on HTTP Status
const int ledCONNECTED = 2; // Toggled on when AP connected
const int sensor1 = 14;
const int sensor2 = 12;
const int open1 = 5;
const int open2 = 4;

// These buttons are exposed on the nodemcu dev board
const int key_user = 16; // What can we do with this button?
const int key_flash = 0; // If pressed within 5 seconds of power on, enter admin mode
// End Pin Assignment

unsigned long secretRandNumber; // We will generate a new secret on startup.

String menuPath = "0";

int lastAccessTime = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


boolean deviceAdmin = 0;

// Define the LED state for ledHTTP
//   This is used for blinking the LED with a non-blocking method
boolean ledHTTPState = LOW;
unsigned long    ledHTTPStateMills = 0;
long    ledHTTPStateInterval = 250; // How fast to blink the LED


void setup ( void ) {
  EEPROM.begin(1024); // 512 bytes should be more than enough (famous last words)
  loadSettings();

  inputString.reserve(50);

  // Set relays as outputs;
  pinMode ( open1, OUTPUT );
  pinMode ( open2, OUTPUT );
  digitalWrite ( open1, 0 );
  digitalWrite ( open2, 0 );


  //  There is a bug in the esp8266 library which prevents the pulldown from functioning
  //    https://github.com/esp8266/Arduino/issues/478
  pinMode ( sensor1, INPUT );
  pinMode ( sensor2, INPUT );

  // Set status LEDs to OUTPUT
  pinMode ( ledHTTP, OUTPUT );
  pinMode ( ledCONNECTED, OUTPUT );
  digitalWrite ( ledHTTP, 0 );
  digitalWrite ( ledCONNECTED, 0 );

  // Get access to the key_user button
  pinMode( key_flash, INPUT_PULLUP );


  delay(5000);
  // Set deviceAdmin to one if key_flash is depressed. Otherwise, use defaults.
  if (digitalRead( key_flash ) == 0) {
    deviceAdmin = 1;
    pinMode( key_flash, OUTPUT );
  } else {
    pinMode( key_flash, OUTPUT );
  }

  Serial.begin ( 115200 );

  if (deviceAdmin) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("yado_admin", "yado_admin");
    //WiFi.mode(WIFI_AP);
    WiFi.config ( IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0)) ;
    delay(10);

	// if DNSServer is started with "*" for domain name, it will reply with
	// provided IP to all DNS request
	dnsServer.start(DNS_PORT, "*", IPAddress(192, 168, 4, 1));

    //WiFi.printDiag(Serial);
    Serial.println ( "Entering admin mode." );

    Serial.print ( "IP address: " );
    Serial.println ( WiFi.softAPIP() );
    printAPMacAddress();

    // We are using the amount of time required to connect to the AP as the seed to a random number generator.
    //   We should look for other ways to improve the seed. This should be "good enough" for now.

    server.on ( "/", handleAdminFrameset );
    server.on ( "/leftnav", handleAdminNav );
    server.on ( "/conf/wifi", handleAdminConfWifi );
    server.on ( "/conf/network", handleAdminConfNetwork );
    server.on ( "/conf/accounts", handleAdminConfAccounts );
    server.on ( "/conf/sensors", handleAdminConfSensors );
    server.on ( "/system/defaults", handleAdminDefaults );
    server.on ( "/system/settings", handleAdminSettings );
    server.on ( "/system/restart", handleAdminRestart);
    server.on ( "/system/apply", handleAdminApply);
    server.on ( "/yado.css", handleCSS);

    server.onNotFound ( handleNotFound );
    server.begin();
    Serial.println ( "HTTP server started" );

  } else {
    WiFi.begin ( settings.ssid, settings.ssidPassword );
    WiFi.mode ( WIFI_STA );



    // Documentation says this is supposed to come before WiFi.begin, but when it is there -- it doesn't work. WHY?!?!?!
    if (settings.ipMode == 1) { // 0 = Dynamic, 1 = Static
      WiFi.config ( settings.ipAddress, settings.ipGateway, settings.ipSubnet) ;
    }

    Serial.println ( "" );

    //EEPROM_readAnything(0, settings);

    // Wait for connection
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }

    digitalWrite ( ledCONNECTED, 1 );

    WiFi.printDiag(Serial);

    Serial.print ( "IP address: " );
    Serial.println ( WiFi.localIP() );
    printMacAddress();

    // We are using the amount of time required to connect to the AP as the seed to a random number generator.
    //   We should look for other ways to improve the seed. This should be "good enough" for now.
    randomSeed(micros());
    secretRandNumber = random(2147483646); // Full range of long 2147483647
    Serial.println("Secret: " + String(secretRandNumber));

    server.on ( "/", handleRoot );
    server.on ( "/externalScript.js", handleExternalScriptJS );
    server.on ( "/json/sensors", handleJSONSensors );
    server.on ( "/json/digest/new", handleJSONDigestNew );
    //    server.on ( "/handleBigResponse", handleBigResponse );
    server.on ( "/yado.css", handleCSS);

    server.onNotFound ( handleNotFound );
    server.begin();
    Serial.println ( "HTTP server started" );
  }

}


void loop ( void ) {

  server.handleClient();
  dnsServer.processNextRequest();
  
  menuLoop() ;

  if (deviceAdmin) {
    unsigned long ledHTTPCurrentMills = millis();

    if (ledHTTPCurrentMills - ledHTTPStateMills > ledHTTPStateInterval) {
      ledHTTPStateMills = ledHTTPCurrentMills;

      if (ledHTTPState) {
        ledHTTPState = 0;
      } else {
        ledHTTPState = 1;
      }
      digitalWrite( ledCONNECTED, ledHTTPState );
      //Serial.println ( WiFi.softAPIP() );
    }

    // If we've been in admin mode for 30 minutes, reboot ESP to get out of
    //   admin mode.
    if (millis() > 1800000) {
      ESP.reset();
    }
  }

}




