// Clear the eeprom of all values.
void eepromClear() {
  for (int i = 0; i < 512; i++)
    EEPROM.write(i, 0);

  EEPROM.end();
}


void printMenu ( String whatMenu ) {

  //strcpy( settings.ssid, "helloworld" ) ;

  //EEPROM_writeAnything(0, settings);

EEPROM_readAnything(0, settings);

  if (whatMenu == "0") {
    Serial.println ( "" ) ;
    Serial.println ( ">>Main Menu -- USB Configuration is currently not fully supported." );
    Serial.println ( "  1) WiFi Setup" );
    Serial.println ( "  2) IP Configuration" );
    Serial.println ( "  3) Access Control" );
    Serial.println ( "  4) Statistics" );
    Serial.println ( "  5) Reset to Factory Settings" );
    Serial.println ( "  6) Reboot Yado" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "1") {
    Serial.println ( "" ) ;
    Serial.println ( ">>WiFi Setup" );
    Serial.println ( "  1) SSID [currentSSID]" );
    Serial.println ( "  2) Wifi Password [currentWifiPassword]" );
    Serial.println ( "  x) Return to Main Menu" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "1.1") {
    Serial.println ( "" ) ;
    Serial.println ( ">>WiFi Setup" );
    Serial.println ( "  Press ENTER to abort." );
    Serial.print ( "  Enter a new SSID (Network Name): " );
  }


  if (whatMenu == "1.2") {
    Serial.println ( "" ) ;
    Serial.println ( ">>WiFi Setup" );
    Serial.println ( "  Press ENTER to abort." );
    Serial.print ( "  Enter a new SSID Password : " );
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
    Serial.println ( ">>Access Control" );
    Serial.println ( "  1) General Password[xxxxxx]" );
    Serial.println ( "  2) Admin Password[xxxxxx]" );
    Serial.println ( "  x) Return to Main Menu" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "4" ) {
    Serial.println ( "" ) ;
    Serial.println ( F(">>Statistics") );
    Serial.println ( "" ) ;
    Serial.println ( "Secret: " + String(secretRandNumber)) ;
    Serial.println ( "Wifi SSID    : " + String(settings.ssid)) ;
    Serial.println ( "Wifi Password: " + String(settings.ssidPassword)) ;
    Serial.println ( "" ) ;
    Serial.println ( "IP Mode: " + String(settings.ipMode));
    Serial.println ( "IP Address: " + String(settings.ipAddress[0]) + "." + String(settings.ipAddress[1]) + "." + String(settings.ipAddress[2]) + "." + String(settings.ipAddress[3])  );
    Serial.println ( "IP Gateway: " + String(settings.ipGateway[0]) + "." + String(settings.ipGateway[1]) + "." + String(settings.ipGateway[2]) + "." + String(settings.ipGateway[3])  );
    Serial.println ( "IP Subnet: " + String(settings.ipSubnet[0]) + "." + String(settings.ipSubnet[1]) + "." + String(settings.ipSubnet[2]) + "." + String(settings.ipSubnet[3])  );
    Serial.println ( F("  x) Return to Main Menu") );
    Serial.println ( "" ) ;
    Serial.print ( F("Make a selection: ") );
  }

  if (whatMenu == "5" ) {
    Serial.println ( "" ) ;
    Serial.println ( F(">>Reset to Factory Settings") );
    Serial.println ( "" ) ;
    Serial.println ( F("  This will reset your Yagdo. Are you sure?") ) ;
    Serial.println ( F("  To Confirm, type: yes") ) ;
    Serial.println ( F("  Otherwise, type: x to return to main menu") ) ;
    Serial.println ( "" ) ;
    Serial.print ( F("Make a selection: ") );
  }

  if (whatMenu == "6" ) {
    Serial.println ( "" ) ;
    Serial.println ( F(">>Reboot Yado") );
    Serial.println ( "" ) ;
    Serial.println ( F("  This will reboot your Yagdo. Are you sure?") ) ;
    Serial.println ( F("  To Confirm, type: yes") ) ;
    Serial.println ( F("  Otherwise, type: x to return to main menu") ) ;
    Serial.println ( "" ) ;
    Serial.print ( F("Make a selection: ") );
  }

}

void menuLoop(void) {

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
      } else if ( inputString == "6" ) {
        menuPath = "6";

        
      }
    } else if (menuPath == "1" ) {
      //printMenu ( "1" );

 

      if ( inputString == "1" ) {
        menuPath = "1.1";
      } else if ( inputString == "2" ) {
        menuPath = "1.2";
      } else if ( inputString == "x" ) {
        menuPath = "0";
      }

    } else if (menuPath == "2" ) {
      //printMenu ( "2" ) ;

      if ( inputString == "1" ) {
        menuPath = "2.1";
      } else if ( inputString == "2" ) {
        menuPath = "2.2";
      } else if ( inputString == "x" ) {
        menuPath = "0";
      }

    } else if (menuPath == "3" ) {
      //printMenu ( "3" ) ;

      if ( inputString == "x" ) {
        menuPath = "0";
      }

    } else if (menuPath == "4" ) {
      //printMenu ( "4" ) ;
      
      if ( inputString == "x" ) {
        menuPath = "0";
      }

    } else if (menuPath == "5" ) {
      //printMenu ( "5" ) ;

      if ( inputString == "x" ) {
        menuPath = "0";
      } else if (inputString == "yes") {
        Serial.println ( "" );
        Serial.print ( "EEPROM Erasing..." ) ;
        eepromClear();      
        Serial.println ( " DONE!" );
        Serial.println ( "" );
        menuPath = "0";
      }

    } else if (menuPath == "6" ) {

      if ( inputString == "x" ) {
        menuPath = "0";
      } else if (inputString == "yes") {
        Serial.println ( "" );
        Serial.println ( "Rebooting..." ) ;

        ESP.reset();
        //for (;;) {
        //}
      }

    }

    inputString = "";
    stringComplete = false;

    printMenu ( menuPath ) ;

  }


}

