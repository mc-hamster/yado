
void handleAdminRoot() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Yado -- Admin Main Menu</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Configure</h2>\n";
  message += "  <br>\n";
  message += "  <a href=/conf/wifi>Wifi</a><br>\n";
  message += "  <a href=/conf/network>Network</a><br>\n";
  message += "  <a href=/conf/accounts>Accounts</a><br>\n";
  message += "  <a href=/conf/sensors>Sensors</a><br>\n";
  message += "  <br>\n";
  message += "  <h2>System</h2>\n";
  message += "  <a href=/system/settings>Display Settings</a><br>\n";
  message += "  <a href=/system/restart>Restart</a> (Leave admin configuration)<br>\n";
  message += "  <a href=/system/apply>Apply New Settings</a><br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "  <br>\n";
  message += "  Auto Restart in ... 30:00\n";
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
  message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Admin Menu</h1>\n";
  message += "  <br>\n";
  message += "  Configure Accounts<br>\n";
  message += "  Configure Sensors<br>\n";
  message += "  <br>\n";
  message += "  Restart Without Applying Settings<br>\n";
  message += "  Apply Changes/No Changes to Apply<br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send ( 200, "text/html", message );
}

void handleAdminConfWifi() {
  boolean saved = 0;

  if (server.arg("ssid") != "" && server.arg("ssidPassword") != "") {
	saved = 1;
		  
	String serverArgSsid = server.arg("ssid");
	String serverArgSsidPassword = server.arg("ssidPassword");
		  
	serverArgSsid.toCharArray(settings.ssid, 32);
	serverArgSsidPassword.toCharArray(settings.ssidPassword, 64);
		  
  }

  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Wifi</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
  message += "</head>\n";
  message += "<body>\n";

  if (saved) {
    message += "<b>Settings saved. Remember to apply settings before restarting.</b><br><br>\n";
  }
  
  message += "<form method=\"post\" action=\"/conf/network\">\n";

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0)
    message += "no networks found";
  else  {
     message += "Select a network (unsecured networks are not supported):<br />\n";

    for (int i = 0; i < n; ++i) {
	  if (WiFi.encryptionType(i) != ENC_TYPE_NONE) {
		  message += "<input type=\"radio\" name=\"ssid\" id=\"radio\" value=\"" + String(WiFi.SSID(i)) + "\" />" + String(WiFi.SSID(i)) + " (" + WiFi.RSSI(i) + ")<br />\n";
	  }
	  // Yield some cpu cycles to IP stack.
	  //   This is important incase the list is large and it takes us tome to return
	  //   to the main loop.
	  delay(5); 
    }
  }
	message += "password <input type=\"text\" name=\"ssidPassword\" id=\"textfield\" size=\"64\" maxlength=\"64\"/><br /><br />";
	message += "<input type=\"submit\" name=\"button\" id=\"button\" value=\"Submit\" />";
	message += "</form>";

	message += "Current ssid: " + String(settings.ssid) + "<br>\n";
	message += "Current ssidPassword: " + String(settings.ssidPassword) + "<br>\n";


	message += "  <a href=/>Main Menu</a><br>\n";

	message += "</body>\n";
	message += "</html>\n";


	server.send ( 200, "text/html", message );
}


void handleAdminConfNetwork() {
	
	
	
	String message = "\n\n";

	message += "<html>\n";
	message += " <head>\n";
	message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
	message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
	message += "  <title>Configure Network</title>\n";
	message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
	message += "</head>\n";
	message += "<body>\n";
	
	message += "<form id=form1 name=form1 method=post action=/conf/network>\n";
	message += "<table border=1>\n";
	message += "<tr>\n";
	message += "<td><p>\n";

	if (settings.ipMode == 1) {
		message += " <input name=ipMode type=radio value=1 checked=checked /> \n";
	} else {
		message += " <input name=ipMode type=radio value=1 /> \n";
	}
	
	message += "Static</p>\n";
	message += "<p>IP: \n";
	message += "<input name=ip_0 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[0]) + " />\n";
	message += "<input name=ip_1 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[1]) + " />\n";
	message += "<input name=ip_2 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[2]) + " />\n";
	message += "<input name=ip_3 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[3]) + " />\n";
	message += "<br />\n";
	message += "Gateway:\n";
	message += "<input name=gateway_0 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[0]) + " />\n";
	message += "<input name=gateway_1 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[1]) + " />\n";
	message += "<input name=gateway_2 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[2]) + " />\n";
	message += "<input name=gateway_3 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[3]) + " />\n";
	message += "<br />\n";
	message += "Subnet:\n";
	message += "<input name=subnet_0 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[0]) + " />\n";
	message += "<input name=subnet_1 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[1]) + " />\n";
	message += "<input name=subnet_2 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[2]) + " />\n";
	message += "<input name=subnet_3 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[3]) + " />\n";
	message += "</p></td>\n";
	message += "</tr>\n";
	message += "<tr>\n";
	message += "<td><p>\n";

	if (settings.ipMode == 0) {
		message += " <input name=ipMode type=radio value=0 checked=checked /> \n";
	} else {
		message += " <input name=ipMode type=radio value=0 /> \n";
	}
		
	message += " Dynamic<br />\n";
	message += " </p>\n";
	message += "<p>Select this to have your router automatically assign an address.<br />\n";
	message += "</p></td>\n";
	message += "</tr>\n";
	message += "</table>\n";
	message += "<input type=submit name=button id=button value=Submit />\n";
	message += "</p>\n";
	message += "</form>\n";	
	
	message += "\n";
	message += "\n";
	message += "  <br>\n";
	message += "  Restart Without Applying Settings<br>\n";
	message += "  Apply Changes/No Changes to Apply<br>\n";
	message += "  <a href=/>Main Menu</a><br>\n";
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
  message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Admin Menu</h1>\n";
  message += "  <br>\n";
  message += "  Configure Accounts<br>\n";
  message += "  Configure Sensors<br>\n";
  message += "  <br>\n";
  message += "  Restart Without Applying Settings<br>\n";
  message += "  Apply Changes/No Changes to Apply<br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
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
  message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Restarting...</h1>\n";
  message += "</body>\n";
  message += "</html>\n";

  server.send ( 200, "text/html", message );

  delay(250);

  ESP.reset();
}

void handleAdminApply() {
	String message = "\n\n";

	message += "<html>\n";
	message += " <head>\n";
	message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
	message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
	message += "  <title>Restarting...</title>\n";
    message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
	message += "</head>\n";
	message += "<body>\n";
	message += "  <h2>Applying new settings...DONE</h1>\n";
    message += "  <a href=/>Main Menu</a><br>\n";
	message += "</body>\n";
	message += "</html>\n";

	server.send ( 200, "text/html", message );

}
void handleAdminSettings () {
	String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Current Settings</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
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
  message += "  <h2>Current Accounts</h1>\n";
  message += "    \"settings.accessGeneral[0].password\" : " + String(settings.accessGeneral[0].password) + "<br>\n";
  message += "    \"settings.accessGeneral[0].note\" : " + String(settings.accessGeneral[0].note) + "<br>\n";
  message += "    \"settings.accessGeneral[1].password\" : " + String(settings.accessGeneral[1].password) + "<br>\n";
  message += "    \"settings.accessGeneral[1].note\" : " + String(settings.accessGeneral[1].note) + "<br>\n";
  message += "    \"settings.accessGeneral[2].password\" : " + String(settings.accessGeneral[2].password) + "<br>\n";
  message += "    \"settings.accessGeneral[2].note\" : " + String(settings.accessGeneral[2].note) + "<br>\n";
  message += "    \"settings.accessGeneral[3].password\" : " + String(settings.accessGeneral[3].password) + "<br>\n";
  message += "    \"settings.accessGeneral[3].note\" : " + String(settings.accessGeneral[3].note) + "<br>\n";
  message += "    \"settings.accessGeneral[4].password\" : " + String(settings.accessGeneral[4].password) + "<br>\n";
  message += "    \"settings.accessGeneral[4].note\" : " + String(settings.accessGeneral[4].note) + "<br>\n";
  message += "  <br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";

	server.send ( 200, "text/html", message );
}
