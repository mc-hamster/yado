

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
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Hash.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"

// Developed using latest ESP8266WebServer from  https://github.com/igrr/Arduino/tree/esp8266/hardware/esp8266com/esp8266/libraries/ESP8266WebServer


// Configuration Start

const char* ssid = "";
const char* password = "";

struct settings_t
{
  char ssid[32];
  char ssidPassword[64];
  char accessAdmin[16];
  char accessGeneral[16];
  uint8_t ipMode; // 0 = Dynamic, 1 = Static
  uint8_t ipAddress[4]; // 255.255.255.255
  uint8_t ipGateway[4]; // 255.255.255.255
  uint8_t ipSubnet[4]; // 255.255.255.255
} settings;

char access[64];

// the IP address for the shield:
IPAddress ipAddress(0, 0, 0, 0);
IPAddress ipGateway(0, 0, 0, 0);
IPAddress ipSubnet(0, 0, 0, 0);

boolean useDHCP = false;  // If false, use manual IP address (above)


int requestTTL = 60;

// Configuration End

ESP8266WebServer server ( 80 );


// Pin Assignment
const int ledHTTP = 0;     // Toggled on HTTP Status
const int ledCONNECTED = 2; // Toggled on when AP connected
const int sensor1 = 14; 
const int sensor2 = 12;
const int open1 = 5;
const int open2 = 4;

// These buttons are exponsed on the nodemcu dev board
const int key_user = 16; // TODO: On startup, if this button is pressed -- broadcast an AP
const int key_flash = 0; 
// End Pin Assignment


unsigned long secretRandNumber; // We will generate a new secret on startup.

String menuPath = "0";

int lastAccessTime = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete



void setup ( void ) {
  EEPROM.begin(512); // 512 bytes should be more than enough (famous last words)
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
  
  Serial.begin ( 115200 );

  // Read settings from EEPROM;
  EEPROM_readAnything(0, settings);



  WiFi.begin ( ssid, password );

  // Documentation says this is supposed to come before WiFi.begin, but when it is there -- it doesn't work. WHY?!?!?!
  if (!useDHCP) { // If true, use manual IP address
    WiFi.config ( ipAddress, ipGateway, ipSubnet) ;
  }
  
  Serial.println ( "" );

  EEPROM_readAnything(0, settings);

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

  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}


void loop ( void ) {
  server.handleClient();

  menuLoop() ;

}




