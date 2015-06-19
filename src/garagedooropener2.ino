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
 * * Neither the name of Majenko Technologies nor the names of its
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
//#include <ESP8266mDNS.h>
#include <Hash.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"


// Configuration Start

const char *ssid = "networkSSID";
const char *password = "networkPassword";

struct settings_t
{
  char ssid[32];
  char ssidPassword[64];
  char accessAdmin[32];
  char accessGeneral[32];
  byte ipAddress[15]; // 255.255.255.255
} settings;

char access[] = "accessPassword";

// the IP address for the shield:
IPAddress ipAddress(10, 11, 12, 36);
//  IPAddress ipDNS(8, 8, 8, 8);
IPAddress ipGateway(10, 11, 12, 1);
IPAddress ipSubnet(255, 255, 255, 0);

int requestTTL = 600;

// Configuration End

ESP8266WebServer server ( 80 );

const int ledHTTP = 0;     // Toggled on HTTP Status

const int sensor1 = 14; // LED connected to digital pin 13
const int sensor2 = 12;   // pushbutton connected to digital pin 7
const int open1 = 5;
const int open2 = 4;

unsigned long secretRandNumber; // We will generate a new secret on startup.

String menuPath = "0";

int lastAccessTime = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

String externJavascriptString = "\n"
                                "function validateForm () { \n"
                                "  var x = document.forms['myForm']['password'].value;\n"
                                "  if (x == null || x == '') {\n"
                                "      alert('Password must be filled');\n"
                                "      return false;\n"
                                "  }\n"
                                "  var requestPassword = CryptoJS.SHA1(document.forms['myForm']['password'].value + document.forms['myForm']['serverDigest'].value);\n"
                                "  document.forms['myForm']['password'].value = '';\n"
                                "  document.forms['myForm']['requestPassword'].value = requestPassword;\n"
                                "  return true; \n"
                                "}\n"
                                "/*CryptoJS v3.1.2\n"
                                "code.google.com/p/crypto-js\n"
                                "(c) 2009-2013 by Jeff Mott. All rights reserved.\n"
                                "code.google.com/p/crypto-js/wiki/License\n"
                                "*/\n"
                                "var CryptoJS=CryptoJS||function(e,m){var p={},j=p.lib={},l=function(){},f=j.Base={extend:function(a){l.prototype=this;var c=new l;a&&c.mixIn(a);c.hasOwnProperty(\"init\")||(c.init=function(){c.$super.init.apply(this,arguments)});c.init.prototype=c;c.$super=this;return c},create:function(){var a=this.extend();a.init.apply(a,arguments);return a},init:function(){},mixIn:function(a){for(var c in a)a.hasOwnProperty(c)&&(this[c]=a[c]);a.hasOwnProperty(\"toString\")&&(this.toString=a.toString)},clone:function(){return this.init.prototype.extend(this)}},\n"
                                "n=j.WordArray=f.extend({init:function(a,c){a=this.words=a||[];this.sigBytes=c!=m?c:4*a.length},toString:function(a){return(a||h).stringify(this)},concat:function(a){var c=this.words,q=a.words,d=this.sigBytes;a=a.sigBytes;this.clamp();if(d%4)for(var b=0;b<a;b++)c[d+b>>>2]|=(q[b>>>2]>>>24-8*(b%4)&255)<<24-8*((d+b)%4);else if(65535<q.length)for(b=0;b<a;b+=4)c[d+b>>>2]=q[b>>>2];else c.push.apply(c,q);this.sigBytes+=a;return this},clamp:function(){var a=this.words,c=this.sigBytes;a[c>>>2]&=4294967295<<\n"
                                "32-8*(c%4);a.length=e.ceil(c/4)},clone:function(){var a=f.clone.call(this);a.words=this.words.slice(0);return a},random:function(a){for(var c=[],b=0;b<a;b+=4)c.push(4294967296*e.random()|0);return new n.init(c,a)}}),b=p.enc={},h=b.Hex={stringify:function(a){var c=a.words;a=a.sigBytes;for(var b=[],d=0;d<a;d++){var f=c[d>>>2]>>>24-8*(d%4)&255;b.push((f>>>4).toString(16));b.push((f&15).toString(16))}return b.join(\"\")},parse:function(a){for(var c=a.length,b=[],d=0;d<c;d+=2)b[d>>>3]|=parseInt(a.substr(d,\n"
                                "2),16)<<24-4*(d%8);return new n.init(b,c/2)}},g=b.Latin1={stringify:function(a){var c=a.words;a=a.sigBytes;for(var b=[],d=0;d<a;d++)b.push(String.fromCharCode(c[d>>>2]>>>24-8*(d%4)&255));return b.join(\"\")},parse:function(a){for(var c=a.length,b=[],d=0;d<c;d++)b[d>>>2]|=(a.charCodeAt(d)&255)<<24-8*(d%4);return new n.init(b,c)}},r=b.Utf8={stringify:function(a){try{return decodeURIComponent(escape(g.stringify(a)))}catch(c){throw Error(\"Malformed UTF-8 data\");}},parse:function(a){return g.parse(unescape(encodeURIComponent(a)))}},\n"
                                "k=j.BufferedBlockAlgorithm=f.extend({reset:function(){this._data=new n.init;this._nDataBytes=0},_append:function(a){\"string\"==typeof a&&(a=r.parse(a));this._data.concat(a);this._nDataBytes+=a.sigBytes},_process:function(a){var c=this._data,b=c.words,d=c.sigBytes,f=this.blockSize,h=d/(4*f),h=a?e.ceil(h):e.max((h|0)-this._minBufferSize,0);a=h*f;d=e.min(4*a,d);if(a){for(var g=0;g<a;g+=f)this._doProcessBlock(b,g);g=b.splice(0,a);c.sigBytes-=d}return new n.init(g,d)},clone:function(){var a=f.clone.call(this);\n"
                                "a._data=this._data.clone();return a},_minBufferSize:0});j.Hasher=k.extend({cfg:f.extend(),init:function(a){this.cfg=this.cfg.extend(a);this.reset()},reset:function(){k.reset.call(this);this._doReset()},update:function(a){this._append(a);this._process();return this},finalize:function(a){a&&this._append(a);return this._doFinalize()},blockSize:16,_createHelper:function(a){return function(c,b){return(new a.init(b)).finalize(c)}},_createHmacHelper:function(a){return function(b,f){return(new s.HMAC.init(a,\n"
                                "f)).finalize(b)}}});var s=p.algo={};return p}(Math);\n"
                                "(function(){var e=CryptoJS,m=e.lib,p=m.WordArray,j=m.Hasher,l=[],m=e.algo.SHA1=j.extend({_doReset:function(){this._hash=new p.init([1732584193,4023233417,2562383102,271733878,3285377520])},_doProcessBlock:function(f,n){for(var b=this._hash.words,h=b[0],g=b[1],e=b[2],k=b[3],j=b[4],a=0;80>a;a++){if(16>a)l[a]=f[n+a]|0;else{var c=l[a-3]^l[a-8]^l[a-14]^l[a-16];l[a]=c<<1|c>>>31}c=(h<<5|h>>>27)+j+l[a];c=20>a?c+((g&e|~g&k)+1518500249):40>a?c+((g^e^k)+1859775393):60>a?c+((g&e|g&k|e&k)-1894007588):c+((g^e^\n"
                                "k)-899497514);j=k;k=e;e=g<<30|g>>>2;g=h;h=c}b[0]=b[0]+h|0;b[1]=b[1]+g|0;b[2]=b[2]+e|0;b[3]=b[3]+k|0;b[4]=b[4]+j|0},_doFinalize:function(){var f=this._data,e=f.words,b=8*this._nDataBytes,h=8*f.sigBytes;e[h>>>5]|=128<<24-h%32;e[(h+64>>>9<<4)+14]=Math.floor(b/4294967296);e[(h+64>>>9<<4)+15]=b;f.sigBytes=4*e.length;this._process();return this._hash},clone:function(){var e=j.clone.call(this);e._hash=this._hash.clone();return e}});e.SHA1=j._createHelper(m);e.HmacSHA1=j._createHmacHelper(m)})();";


// Clear the eeprom of all values.
void eepromClear() {
  for (int i = 0; i < 512; i++)
    EEPROM.write(i, 0);

  EEPROM.end();
}

void handleRoot() {
  digitalWrite ( ledHTTP, 1 );


  // TODO: Have this be configurable

  char temp[2000];
  int sec = millis() / 1000; // TODO: Revert to the previous line. This is here for debugging.
  int min = sec / 60;
  int hr = min / 60;

  char requestRangeValid = 0;

  uint8_t digest[20];
  uint8_t digest2[20];
  String preDigest;

  preDigest = sec;
  preDigest += "x";
  preDigest += String(secretRandNumber);

  sha1(preDigest, &digest[0]);

  char digestStringHex[41];
  char digestStringHex2[41];

  for (int i = 0; i < 20; i++) {
    sprintf(&digestStringHex[i * 2], "%02x", digest[i]);
  }

  String requestTime = server.arg("time");

  if ( requestTime.toInt() ) {

    // Request time has to be less than or equal to the current time.
    //  If it were bigger, then we have a big problem. Will this condition need to be addressed?
    //
    // Request time + TTL must not be greater than current time
    if ((requestTime.toInt() <= sec)
        && (requestTime.toInt() >= sec - requestTTL)) {

      requestRangeValid = 1;


    } else {
      // Serial.println ( "** Request out of range" );

    }



  }

  String preDigest2;

  preDigest2 = requestTime.toInt();
  preDigest2 += "x";
  preDigest2 += String(secretRandNumber);
  //preDigest2 += "Secret";

  sha1(preDigest2, &digest2[0]);
  for (int i = 0; i < 20; i++) {
    sprintf(&digestStringHex2[i * 2], "%02x", digest2[i]);
  }

  String preDigest3 = access;

  preDigest3 += digestStringHex2;

  sha1(preDigest3, &digest2[0]);

  for (int i = 0; i < 20; i++) {
    sprintf(&digestStringHex2[i * 2], "%02x", digest2[i]);
  }

  //Serial.println ( digestStringHex2);

  if (requestRangeValid == 1 &&
      server.arg("requestPassword") == digestStringHex2) {

    // Ensure that the requestTime is greater than the last successfull access time.
    //  This will guarentee that packets are not replayed. 
    if (requestTime.toInt() > lastAccessTime) {
      lastAccessTime = requestTime.toInt();
      Serial.println ( "Yay!" );
      digitalWrite ( open1, 1 );
      delay(100);
      digitalWrite ( open1, 0 );
    }

  } else {
    if (requestRangeValid == 1) {
      Serial.println ( "Invalid digest recieved." );
    }
  }

  char upTimeString[20];
  snprintf ( upTimeString, 20, "%02d:%02d:%02d", hr, min % 60, sec % 60) ; // 00:38:47 0123456789

  snprintf ( temp, 2000,

             "<html>\
  <head>\
    <meta http-equiv='refresh' content='%d; url=/'/>\
    <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\
    <title>Garage Door Opener</title>\
    <script src='externalScript.js'></script>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h2>Garage Door Opener</h1>\
    Sensor1: %d Sensor2: %d <br>\
    <form name=myForm method=get onsubmit=\"return validateForm()\" >\
    <input type=hidden name=time value=%d><br>\
    Password: <input type=password name=password value=><br>\
    <!-- Request Password (Computed in Javascript) : --><input type=hidden size=50 name=requestPassword>\
    <!-- Server Digest:  --><input type=hidden name=serverDigest value=%20s size=50>\
    <input type=submit value=Open>\
    </form>\
    <p>Uptime: %20s</p>\
  </body>\
</html>",

             requestTTL, digitalRead(sensor1), digitalRead(sensor2), sec, digestStringHex, upTimeString
           );

  server.send ( 200, "text/html", temp );
  digitalWrite ( ledHTTP, 0 );
}

void handleNotFound() {
  digitalWrite ( ledHTTP, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }


  server.send ( 404, "text/plain", message );
  digitalWrite ( ledHTTP, 0 );
}

void handleJSONSensors () {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += "{\n";
  message += "  \"data\" : {\n";
  message += "    \"sensor1\" : " + String(digitalRead(sensor1)) + ",\n";
  message += "    \"sensor2\" : " + String(digitalRead(sensor2)) + "\n";
  message += "  }\n";
  message += "}\n";

  server.send ( 200, "text/plain", message );

  digitalWrite ( ledHTTP, 0 );
}

void handleExternalScriptJS() {
  digitalWrite ( ledHTTP, 1 );

  if (0) {
    // TODO: If we recieve a If-None-Match header and it matches the Etag we defined, then
    //       return a  HTTP 304 Not Modified header with no content.
    //       -- See: http://en.wikipedia.org/wiki/HTTP_ETag for protocol details
  } else {

    // This is CryptoJS from google. Pasted here so not to require internet access.



    // Define header to encourage browsers to cache this page.
    server.sendHeader ( "ETag", "CacheThisForever", 0 );
    server.sendHeader ( "Expires", "Mon, 08 Jun 2035 00:19:36 GMT", 0 );
    server.sendHeader ( "Cache-Control", "public, max-age=31536000", 0 ); // 31536000 = 1 year
    //delay ( 5 ) ;
    server.send ( 200, "text/plain", externJavascriptString );
    //Serial.print ( message );
    //delay ( 5 ) ;
    //server.send ( 200, "text/javascript", "asdf" );
  }

  digitalWrite ( ledHTTP, 0 );
}

void setup ( void ) {
  EEPROM.begin(512); // 512 bytes should be more than enough (famous last words)
  inputString.reserve(50);

  // Set sensors as inputs
  pinMode ( sensor1, INPUT );
  pinMode ( sensor2, INPUT );

  pinMode ( ledHTTP, OUTPUT );
  digitalWrite ( ledHTTP, 0 );

  Serial.begin ( 115200 );



  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  EEPROM_readAnything(0, settings);

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  if (1) { // If true, use manual IP address
    WiFi.config ( ipAddress, ipGateway, ipSubnet) ;
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  // We are using the amount of time required to connect to the AP as the seed to a random number generator.
  //   We should look for other ways to improve the seed. This should be "good enough" for now.
  randomSeed(micros());
  secretRandNumber = random(2147483646); // Full range of long 2147483647
  Serial.println("Secret " + String(secretRandNumber));

  server.on ( "/", handleRoot );
  server.on ( "/externalScript.js", handleExternalScriptJS );
  server.on ( "/json/sensors", handleJSONSensors );

  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void printMenu ( String whatMenu ) {

  if (whatMenu == "0") {
    Serial.println ( "" ) ;
    Serial.println ( ">>Main Menu" );
    Serial.println ( "  1) WiFi Setup" );
    Serial.println ( "  2) IP Configuration" );
    Serial.println ( "  3) Access Control" );
    Serial.println ( "  4) Statistics" );
    Serial.println ( "  5) Reset to Factory Settings" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "1") {
    Serial.println ( "" ) ;
    Serial.println ( ">>WiFi Setup" );
    Serial.println ( "  1) Mode [currentMode]" );
    Serial.println ( "  2) SSID [currentSSID]" );
    Serial.println ( "  3) Wifi Password [currentWifiPassword]" );
    Serial.println ( "  x) Return to Main Menu" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "2") {
    Serial.println ( "" ) ;
    Serial.println ( ">>IP Configuration" );
    Serial.println ( "  1) IP Mode [Dynamic/Manual]" );
    Serial.println ( "  2) IP [w.x.y.z]" );
    Serial.println ( "  3) IP Subnet [255.255.255.0]" );
    Serial.println ( "  x) Return to Main Menu" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "3") {
    Serial.println ( "" ) ;
    Serial.println ( ">>IP Configuration" );
    Serial.println ( "  1) IP Mode [Dynamic/Manual]" );
    Serial.println ( "  2) IP [w.x.y.z]" );
    Serial.println ( "  3) IP Subnet [255.255.255.0]" );
    Serial.println ( "  x) Return to Main Menu" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "4" ) {
    Serial.println ( "" ) ;
    Serial.println ( ">>Statistics" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "5" ) {
    Serial.println ( "" ) ;
    Serial.println ( ">>Reset to Factory Settings" );
    Serial.println ( "" ) ;
    Serial.println ( "  This will reset your Yagdo. Are you sure?" ) ;
    Serial.println ( "  To Confirm, type: yes" ) ;
    Serial.println ( "  Otherwise, type: x to return to main menu" ) ;
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

}

void loop ( void ) {
  server.handleClient();

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    // if the incoming character is a newline or carrage return, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    } else {
      // add it to the inputString:
      inputString += inChar;
    }


    Serial.print ( inChar ) ;
  }

  if (stringComplete) {
    //Serial.println("-- " + inputString);
    // clear the string:

    //Serial.println ( "--" + inputString + "--" );
    //Serial.println ( "--" + menuPath + "++" );

    if (menuPath == "0") {

      if ( inputString == "1" ) {
        menuPath = "1";
      } else if ( inputString == "2" ) {
        menuPath = "2";
      } else if ( inputString == "3" ) {
        menuPath = "3";
      } else if ( inputString == "4" ) {
        menuPath = "4";
      } else if ( inputString == "5" ) {
        menuPath = "5";
      }
    } else if (menuPath == "1" ) {
      printMenu ( "1" );

      if ( inputString == "x" ) {
        menuPath = "0";
      }

    } else if (menuPath == "2" ) {
      printMenu ( "2" ) ;

      if ( inputString == "x" ) {
        menuPath = "0";
      }

    } else if (menuPath == "3" ) {
      printMenu ( "3" ) ;

      if ( inputString == "x" ) {
        menuPath = "0";
      }

    } else if (menuPath == "4" ) {
      printMenu ( "4" ) ;

    } else if (menuPath == "5" ) {
      printMenu ( "5" ) ;

      if ( inputString == "x" ) {
        menuPath = "0";
      }

    }

    inputString = "";
    stringComplete = false;

    printMenu ( menuPath ) ;

  }



}





