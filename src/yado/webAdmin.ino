
void handleAdminRoot() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
//  message += "  <meta http-equiv='refresh' content='"  +  String(requestTTL) + "; url=/'/>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Garage Door Opener - Admin</title>\n";
  //  message += "  <!script src='externalScript.js'></script>\n";
  //  message += "  <script src='http://crypto-js.googlecode.com/svn/tags/3.1.2/build/rollups/sha1.js'></script>\n";
  message += "  <script>\n";

  message += "function validateForm () { \n";
	  message += "  var x = document.forms['myForm']['password'].value;\n";
	  message += "  if (x == null || x == '') {\n";
		  message += "      alert('Password must be filled');\n";
		  message += "      return false;\n";
	  message += "  }\n";
	  message += "  var requestPassword = CryptoJS.SHA1(document.forms['myForm']['password'].value + document.forms['myForm']['serverDigest'].value);\n";
	  message += "  document.forms['myForm']['password'].value = '';\n";
	  message += "  document.forms['myForm']['requestPassword'].value = requestPassword;\n";
	  message += "  return true; \n";
  message += "}\n";
  message += "  </script>\n";
  message += "  <style>\n";
  message += "    body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n";
  message += "  </style>\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2><a href=/>Garage Door Opener</a></h1>\n";
  message += "  <form name=myForm method=get onsubmit=\"return validateForm()\" >\n";
  message += "  Sensor 1 Status: "  +  readSensor(1) + " <br>\n";
  message += "  <br>\n";
//  message += "  " + errorString + "<br>\n";
  //message += "  <br>\n";
  //message += "  Sensor 2 Status: "  +  readSensor(2) + " <br>\n";
  //message += "  <input type=hidden name=time value="  +  String(sec) + "><br>\n";
  message += "  Password: <input type=password name=password value=><br>\n";
  //message += "  <!-- Request Password (Computed in Javascript) : --><input type=hidden size=50 name=requestPassword>\n";
  //message += "  <!-- Server Digest:  --><input type=hidden name=serverDigest value="  +  String(digestStringHex) + " size=50>\n";
  message += "  <input type=submit value=Open>\n";
  message += "  </form>\n";
  //message += "  <p>Uptime: "  +  String(upTimeString) + "</p>\n";
  message += "</body>\n";
  message += "</html>\n";

  server.send ( 200, "text/html", message );
}