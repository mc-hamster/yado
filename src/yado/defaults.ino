void loadSettings ( void ) {

  EEPROM_readAnything(0, settings);

};

void defaults ( void ) {
	
	settings.initialized = 1;

	settings.ipAddress[0] = 10;
	settings.ipAddress[1] = 11;
	settings.ipAddress[2] = 12;
	settings.ipAddress[3] = 36;
	
	settings.ipGateway[0] = 10;
	settings.ipGateway[1] = 11;
	settings.ipGateway[2] = 12;
	settings.ipGateway[3] = 1;
	
	settings.ipSubnet[0] = 255;
	settings.ipSubnet[1] = 255;
	settings.ipSubnet[2] = 255;
	settings.ipSubnet[3] = 0;
	
	settings.ipMode = 1; // 0 = Dynamic, 1 = Static
	
	strncpy(settings.ssid, "default_ssid", 32);
	strncpy(settings.ssidPassword, "password", 64);

	strncpy(settings.accessGeneral[0].password, "default", passwordLength);
	strncpy(settings.accessGeneral[1].password, "", passwordLength);
	strncpy(settings.accessGeneral[2].password, "", passwordLength);
	strncpy(settings.accessGeneral[3].password, "", passwordLength);
	strncpy(settings.accessGeneral[4].password, "", passwordLength);

}