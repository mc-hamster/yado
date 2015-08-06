


void printMenu ( String whatMenu ) {

  if (whatMenu == "0") {
    Serial.println ( "" ) ;
    Serial.println ( ">>Main Menu -- USB Configuration is currently not fully supported." );
    Serial.println ( "  1) Statistics" );
    Serial.println ( "" ) ;
    Serial.print ( "Make a selection: " );
  }

  if (whatMenu == "1" ) {
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
      }
    } else if (menuPath == "1" ) {
      if ( inputString == "x" ) {
        menuPath = "0";
      }
	}

    inputString = "";
    stringComplete = false;

    printMenu ( menuPath ) ;

  }


}

