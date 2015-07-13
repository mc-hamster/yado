void loadSettings ( void ) {
	
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
	
	settings.ipMode = 0; // 0 = Dynamic, 1 = Static
	
	strncpy(settings.ssid, "ssid_name_here", 32);
	strncpy(settings.ssidPassword, "ssid_password_here", 64);


	strncpy(settings.accessGeneral[0].password, "access_passworda", passwordLength);
	strncpy(settings.accessGeneral[1].password, "access_passwordb", passwordLength);
	strncpy(settings.accessGeneral[2].password, "access_passwordc", passwordLength);
	strncpy(settings.accessGeneral[3].password, "access_passwordd", passwordLength);
	strncpy(settings.accessGeneral[4].password, "access_passworde", passwordLength);

	requestTTL = 600;
};