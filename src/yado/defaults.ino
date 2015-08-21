void loadSettings ( void ) {

  EEPROM_readAnything(0, settings);

  // If
  if (settings.initialized != 1) {
    loadDefaults();
  }

};

void loadDefaults( void ) {

  // If initialized is anything but 1, programmatically set defaults. This is useful for initial configuration.
  settings.initialized = 1;

  // Set default IP address
  settings.ipAddress[0] = 192;
  settings.ipAddress[1] = 168;
  settings.ipAddress[2] = 1;
  settings.ipAddress[3] = 100;

  settings.ipGateway[0] = 192;
  settings.ipGateway[1] = 168;
  settings.ipGateway[2] = 1;
  settings.ipGateway[3] = 1;

  settings.ipSubnet[0] = 255;
  settings.ipSubnet[1] = 255;
  settings.ipSubnet[2] = 255;
  settings.ipSubnet[3] = 0;

  // Set defaults for IP acquisition default
  settings.ipMode = 1; // 0 = Dynamic, 1 = Static

  // Set defaults for wifi access
  strncpy(settings.ssid, "default_ssid", 32);
  strncpy(settings.ssidPassword, "password", 64);


  // Set defaults for access passwords
  strncpy(settings.accessGeneral[0].password, "default", passwordLength);
  strncpy(settings.accessGeneral[1].password, "", passwordLength);
  strncpy(settings.accessGeneral[2].password, "", passwordLength);
  strncpy(settings.accessGeneral[3].password, "", passwordLength);
  strncpy(settings.accessGeneral[4].password, "", passwordLength);

  strncpy(settings.accessGeneral[0].note, "", noteLength);
  strncpy(settings.accessGeneral[1].note, "", noteLength);
  strncpy(settings.accessGeneral[2].note, "", noteLength);
  strncpy(settings.accessGeneral[3].note, "", noteLength);
  strncpy(settings.accessGeneral[4].note, "", noteLength);


  // Set defaults for contact sensor 1
  settings.contactSensor[0].enabled = 0;
  settings.contactSensor[0].invert  = 1;
  strncpy(settings.contactSensor[0].high, "Open", sensorLabelLength);
  strncpy(settings.contactSensor[0].low,  "Closed", sensorLabelLength);

  // Set defaults for contact sensor 2
  settings.contactSensor[1].enabled = 0;
  settings.contactSensor[1].invert  = 1;
  strncpy(settings.contactSensor[1].high, "Open", sensorLabelLength);
  strncpy(settings.contactSensor[1].low,  "Closed", sensorLabelLength);

  // Set defaults for temperature sensor
  settings.temperature.enabled = 0;
  settings.temperature.metricImperial = 1;


}
