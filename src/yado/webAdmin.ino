
void handleAdminRoot() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Restarting...</title>\n";
  message += "  <style>\n";
  message += "    body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  message += "  </style>\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Current Settings</h1>\n";
  message += "  <br>\n";
  message += "    \"settings.ssid\" : " + String(settings.ssid) + "<br>\n";
  message += "    \"settings.ssidPassword\" : " + String(settings.ssidPassword) + "<br>\n";
  message += "    \"settings.ipMode\" : " + String(settings.ipMode) + "<br>\n";
  message += "    \"settings.ipAddress\" : " + String(settings.ipAddress[0]) + "." + String(settings.ipAddress[1]) + "." + String(settings.ipAddress[2]) + "." + String(settings.ipAddress[3]) + "<br>\n";
  message += "    \"settings.ipGateway\" : " + String(settings.ipGateway[0]) + "." + String(settings.ipGateway[1]) + "." + String(settings.ipGateway[2]) + "." + String(settings.ipGateway[3]) + "<br>\n";
  message += "    \"settings.ipSubnet\" : " + String(settings.ipSubnet[0]) + "." + String(settings.ipSubnet[1]) + "." + String(settings.ipSubnet[2]) + "." + String(settings.ipSubnet[3]) + "<br>\n";
  message += "  <br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send ( 200, "text/html", message );
}

void handleAdminConfAccounts() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Accounts</title>\n";
  message += "  <style>\n";
  message += "    body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  message += "  </style>\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Admin Menu</h1>\n";
  message += "  <br>\n";
  message += "  Configure Accounts<br>\n";
  message += "  Configure Sensors<br>\n";
  message += "  <br>\n";
  message += "  Restart Without Applying Settings<br>\n";
  message += "  Apply Changes/No Changes to Apply<br>\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send ( 200, "text/html", message );
}

void handleAdminConfWifi() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Wifi</title>\n";
  message += "  <style>\n";
  message += "    body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  message += "  </style>\n";
  message += "</head>\n";
  message += "<body>\n";


  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0)
    message += "no networks found";
  else  {
    message += String(n);
    message += " networks found<br>";
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      message += String(i + 1);
      message += ": ";
      message += WiFi.SSID(i);
      message += " (";
      message += WiFi.RSSI(i);
      message += ")";
      message += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
      message += "<br>";
      delay(10);
    }
  }
  //Serial.println("");


  message += "</body>\n";
  message += "</html>\n";


  server.send ( 200, "text/html", message );
}

void handleAdminConfSensors() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Sensors</title>\n";
  message += "  <style>\n";
  message += "    body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  message += "  </style>\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Admin Menu</h1>\n";
  message += "  <br>\n";
  message += "  Configure Accounts<br>\n";
  message += "  Configure Sensors<br>\n";
  message += "  <br>\n";
  message += "  Restart Without Applying Settings<br>\n";
  message += "  Apply Changes/No Changes to Apply<br>\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send ( 200, "text/html", message );
}


void handleAdminRestart() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Restarting...</title>\n";
  message += "  <style>\n";
  message += "    body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  message += "  </style>\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Restarting...</h1>\n";
  message += "</body>\n";
  message += "</html>\n";

  server.send ( 200, "text/html", message );

  delay(250);

  ESP.reset();
}

void handleAdminConfDisplay () {
	String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Restarting...</title>\n";
  message += "  <style>\n";
  message += "    body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  message += "  </style>\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Current Settings</h1>\n";
  message += "  <br>\n";
  message += "    \"settings.ssid\" : " + String(settings.ssid) + "<br>\n";
  message += "    \"settings.ssidPassword\" : " + String(settings.ssidPassword) + "<br>\n";
  message += "    \"settings.ipMode\" : " + String(settings.ipMode) + " (0 = Dynamic; 1 = Static)<br>\n";
  message += "    \"settings.ipAddress\" : " + String(settings.ipAddress[0]) + "." + String(settings.ipAddress[1]) + "." + String(settings.ipAddress[2]) + "." + String(settings.ipAddress[3]) + "<br>\n";
  message += "    \"settings.ipGateway\" : " + String(settings.ipGateway[0]) + "." + String(settings.ipGateway[1]) + "." + String(settings.ipGateway[2]) + "." + String(settings.ipGateway[3]) + "<br>\n";
  message += "    \"settings.ipSubnet\" : " + String(settings.ipSubnet[0]) + "." + String(settings.ipSubnet[1]) + "." + String(settings.ipSubnet[2]) + "." + String(settings.ipSubnet[3]) + "<br>\n";
  message += "  <br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";

	server.send ( 200, "text/html", message );
}
