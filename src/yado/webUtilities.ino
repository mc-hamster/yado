
// Our own version of 'send' which is otherwise in the ESP8266WebServer library. Much inproved without
//   the performance issue in the stock library. We may be able to get rid of this some time in the
//   future if the library's version of send is fixed.
void sendMime (String mimeType, String message) {
  WiFiClient client = httpServer.client();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: " + mimeType);
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Content-Length: " + String(message.length()));
  client.println("");
  client.print(message);
  //	delay(1); // Give the web browser time to receive the data.
  client.stop();
}



void computeServerDigest( int sec, char digestStringHex[] ) {

  uint8_t digest[20];
  String preDigest;

  preDigest = sec;
  preDigest += "x";
  preDigest += String(secretRandNumber);

  sha1(preDigest, &digest[0]);

  for (int i = 0; i < 20; i++) {
    sprintf(&digestStringHex[i * 2], "%02x", digest[i]);
  }

}

// Validates that the password entered is actually valid.
//  TODO: Let this validate from a list of passwords rather than just one.
boolean validatePassword ( int timeFromClient, String digestFromClient ) {

  for (int accountObj = 0; accountObj < numberOfUsers; accountObj++) {

    char serverDigestHex[41];       // Without secret
    uint8_t serverDigestSecret[20]; // With secret
    char serverDigestSecretHex[41]; // With secret

    String preDigest = "";

    computeServerDigest(timeFromClient, serverDigestHex);


    preDigest = settings.accessGeneral[accountObj].password;
    preDigest += serverDigestHex;

    sha1(preDigest, &serverDigestSecret[0]);


    // Convert array of decimal into array of ascii hex values
    for (int i = 0; i < 20; i++) {
      sprintf(&serverDigestSecretHex[i * 2], "%02x", serverDigestSecret[i]);
    }

    if (String(serverDigestSecretHex) == digestFromClient) {
      return true;
    }

  }
  return false;

}

String readSensor ( uint8_t sensor ) {

  if (sensor == 0) {
    if (settings.contactSensor[0].invert == 1) {
      if (digitalRead(sensor1)) {
        return String(settings.contactSensor[0].high);
      } else {
        return String(settings.contactSensor[0].low);
      }
    } else {
      if (digitalRead(sensor1)) {
        return String(settings.contactSensor[0].low);
      } else {
        return String(settings.contactSensor[0].high);
      }
    }
  }


  if (sensor == 1) {
    if (settings.contactSensor[1].invert == 1) {
      if (digitalRead(sensor2)) {
        return String(settings.contactSensor[1].high);
      } else {
        return String(settings.contactSensor[1].low);
      }
    } else {
      if (digitalRead(sensor2)) {
        return String(settings.contactSensor[1].low);
      } else {
        return String(settings.contactSensor[1].high);
      }
    }
  }

  return "Sensor Read Error.";
}
