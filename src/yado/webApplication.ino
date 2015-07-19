
//char tempArray[5000];

void handleExternalScriptJS() {
  digitalWrite ( ledHTTP, 1 );


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



  if (0) {
    // TODO: If we recieve a If-None-Match header and it matches the Etag we defined, then
    //       return a  HTTP 304 Not Modified header with no content.
    //       -- See: http://en.wikipedia.org/wiki/HTTP_ETag for protocol details
  } else {


    // Define header to encourage browsers to cache this page.
    server.sendHeader ( "ETag", "CacheThisForever", 0 );
    server.sendHeader ( "Expires", "Mon, 08 Jun 2035 00:19:36 GMT", 0 );
    server.sendHeader ( "Cache-Control", "public, max-age=31536000", 0 ); // 31536000 = 1 year
    server.send ( 200, "text/plain", externJavascriptString );
  }

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

  server.send ( 200, "application/json", message );

  digitalWrite ( ledHTTP, 0 );
}

void handleJSONDigestNew () {
  digitalWrite ( ledHTTP, 1 );

  int sec = millis() / 1000; // TODO: Revert to the previous line. This is here for debugging.
  char digestStringHex[41];

  computeServerDigest(sec, digestStringHex);

  String message = "";
  message += "{\n";
	  message += "  \"data\" : {\n";
		  message += "    \"sec\" : " + String(sec) + ",\n";
		  message += "    \"digest\" : \"" + String(digestStringHex) + "\"\n";
	  message += "  }\n";
  message += "}\n";

  server.send ( 200, "application/json", message );

  digitalWrite ( ledHTTP, 0 );
}

void handleRoot() {
  digitalWrite ( ledHTTP, 1 );

  // TODO: Have this be configurable

  int sec = millis() / 1000; // TODO: Revert to the previous line. This is here for debugging.
  int min = sec / 60;
  int hr = min / 60;

  char requestRangeValid = 0;
  char digestStringHex[41];

  computeServerDigest(sec, digestStringHex);

  uint8_t digest2[20];

  char digestStringHex2[41];

  String requestTime = server.arg("time");
  String errorString = "";

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
	  errorString = "Your request was too old. Try again.";
    }
  }


  computeServerDigest(requestTime.toInt(), digestStringHex2);


  // Only do something if the password is provided.
  if ( server.arg("requestPassword") != "") {
	  
	  boolean isPasswordValid = validatePassword ( requestTime.toInt(), server.arg("requestPassword") );

	  if (requestRangeValid == 1 && isPasswordValid == true) {

		  // Ensure that the requestTime is greater than the last successfully access time.
		  //  This will guarentee that packets are not replayed.
		  if (requestTime.toInt() > lastAccessTime) {
			  errorString = "Yay!";
			  lastAccessTime = requestTime.toInt();
			  Serial.println ( "Yay!" );
			  digitalWrite ( open1, 1 );
			  digitalWrite ( ledCONNECTED, 0 );
			  delay(200);
			  digitalWrite ( open1, 0 );
			  digitalWrite ( ledCONNECTED, 1 );
		  } else {
			  errorString = "Try again.";
		  }

		  } else {
		  if (requestRangeValid == 1) {
			  Serial.println ( "Invalid digest received." );
			  errorString = "Wrong password.";
			  //} else {
			  //errorString = "Try again.";
		  }
	  }
  }

  char upTimeString[20];

  snprintf ( upTimeString, 20, "%02d:%02d:%02d", hr, min % 60, sec % 60) ; // 00:38:47 0123456789

  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta http-equiv='refresh' content='"  +  String(requestTTL) + "; url=/'/>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Garage Door Opener</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/yado.css\">\n";
//  message += "  <!script src='externalScript.js'></script>\n";
  message += "  <script src='http://crypto-js.googlecode.com/svn/tags/3.1.2/build/rollups/sha1.js'></script>\n";
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
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2><a href=/>Garage Door Opener</a></h1>\n";
  message += "  <form name=myForm method=get onsubmit=\"return validateForm()\" >\n";
  message += "  Sensor 1 Status: "  +  readSensor(1) + " <br>\n";
  message += "  <br>\n";
  message += "  " + errorString + "<br>\n";
  //message += "  <br>\n";
  //message += "  Sensor 2 Status: "  +  readSensor(2) + " <br>\n";
  message += "  <input type=hidden name=time value="  +  String(sec) + "><br>\n";
  message += "  Password: <input type=password name=password value=><br>\n";
  message += "  <!-- Request Password (Computed in Javascript) : --><input type=hidden size=50 name=requestPassword>\n";
  message += "  <!-- Server Digest:  --><input type=hidden name=serverDigest value="  +  String(digestStringHex) + " size=50>\n";
  message += "  <input type=submit value=Open>\n";
  message += "  </form>\n";
  message += "  <p>Uptime: "  +  String(upTimeString) + "</p>\n";
  message += "</body>\n";
  message += "</html>\n";

  server.send ( 200, "text/html", message );
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

void handleCSS () {
	digitalWrite ( ledHTTP, 1 );

	String message = "";
	message += "@charset \"UTF-8\";\n";
	message += "body {\n";
	message += "background-color: #FFFFCC;\n";
	message += "font-family: Arial, Helvetica, sans-serif;\n";
	message += "font-size: 12px;\n";
	message += "line-height: 24px;\n";
	message += "color: #333333;\n";
	message += "}\n";
	message += "td, th {\n";
	message += "font-family: Arial, Helvetica, sans-serif;\n";
	message += "font-size: 12px;\n";
	message += "line-height: 24px;\n";
	message += "color: #330000;\n";
	message += "}\n";
	message += "a {\n";
	message += "color: #330000;\n";
	message += "}\n";
	message += "form {\n";
	message += "background-color: #CCCC99;\n";
	message += "}\n";
	message += ".title {\n";
	message += "font-family: Georgia, \"Times New Roman\", Times, serif;\n";
	message += "font-size: 18px;\n";
	message += "line-height: 30px;\n";
	message += "background-color: #990000; color: #FFFF66;\n";
	message += "}\n";
	message += ".subtitle {\n";
	message += "font-family: Georgia, \"Times New Roman\", Times, serif;\n";
	message += "font-size: 16px;\n";
	message += "line-height: 20px;\n";
	message += "font-weight: bold;\n";
	message += "color: #660000; font-style: oblique;\n";
	message += "}\n";
	message += ".header {\n";
	message += "font-family: Georgia, \"Times New Roman\", Times, serif;\n";
	message += "font-size: 24px;\n";
	message += "background-color: #990000;\n";
	message += "color: #FFFF66;\n";
	message += "}\n";
	message += ".nav {\n";
	message += "font-family: Georgia, \"Times New Roman\", Times, serif;\n";
	message += "font-size: 12px;\n";
	message += "font-weight: bold;\n";
	message += "background-color: #CCCC66;\n";
	message += "}\n";
	message += ".navLink {\n";
	message += "font-family: Arial, Helvetica, sans-serif;\n";
	message += "font-size: 14px;\n";
	message += "font-weight: bold;\n";
	message += "background-color: #DEDECA;\n";
	message += "}\n";
	message += "a:hover {\n";
	message += "color: #DEDECA;\n";
	message += "background-color: #330000;\n";
	message += "}\n";
	message += ".sidebar {\n";
	message += "font-family: Georgia, \"Times New Roman\", Times, serif;\n";
	message += "font-size: 12px;\n";
	message += "line-height: 18px;\n";
	message += "padding: 3px;\n";
	message += "background-color: #FFFF99;\n";
	message += "}\n";
	message += ".sidebarHeader {\n";
	message += "font-family: Georgia, \"Times New Roman\", Times, serif;\n";
	message += "font-size: 14px;\n";
	message += "line-height: 18px;\n";
	message += "color: #FFFF99;\n";
	message += "background-color: #999933;\n";
	message += "font-weight: bold;\n";

    //server.sendHeader ( "ETag", "CacheThisForever", 0 );
    //server.sendHeader ( "Expires", "Mon, 08 Jun 2035 00:19:36 GMT", 0 );
    //server.sendHeader ( "Cache-Control", "public, max-age=31536000", 0 ); // 31536000 = 1 year

	//server.send ( 200, "text/css", message );
	sendMime ( "text/css", message );

	digitalWrite ( ledHTTP, 0 );
}