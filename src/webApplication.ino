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




void handleExternalScriptJS() {
  digitalWrite ( ledHTTP, 1 );

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

  server.send ( 200, "text/plain", message );

  digitalWrite ( ledHTTP, 0 );
}

void handleRoot() {
  digitalWrite ( ledHTTP, 1 );


  // TODO: Have this be configurable

  char temp[2000];
  int sec = millis() / 1000; // TODO: Revert to the previous line. This is here for debugging.
  int min = sec / 60;
  int hr = min / 60;

  char requestRangeValid = 0;

  uint8_t digest[20];
  uint8_t digest2[20];
  String preDigest;

  preDigest = sec;
  preDigest += "x";
  preDigest += String(secretRandNumber);

  sha1(preDigest, &digest[0]);

  char digestStringHex[41];
  char digestStringHex2[41];

  for (int i = 0; i < 20; i++) {
    sprintf(&digestStringHex[i * 2], "%02x", digest[i]);
  }

  String requestTime = server.arg("time");

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

    }



  }

  String preDigest2;

  preDigest2 = requestTime.toInt();
  preDigest2 += "x";
  preDigest2 += String(secretRandNumber);
  //preDigest2 += "Secret";

  sha1(preDigest2, &digest2[0]);
  for (int i = 0; i < 20; i++) {
    sprintf(&digestStringHex2[i * 2], "%02x", digest2[i]);
  }

  String preDigest3 = access;

  preDigest3 += digestStringHex2;

  sha1(preDigest3, &digest2[0]);

  for (int i = 0; i < 20; i++) {
    sprintf(&digestStringHex2[i * 2], "%02x", digest2[i]);
  }

  //Serial.println ( digestStringHex2);

  if (requestRangeValid == 1 &&
      server.arg("requestPassword") == digestStringHex2) {

    // Ensure that the requestTime is greater than the last successfull access time.
    //  This will guarentee that packets are not replayed. 
    if (requestTime.toInt() > lastAccessTime) {
      lastAccessTime = requestTime.toInt();
      Serial.println ( "Yay!" );
      digitalWrite ( open1, 1 );
      delay(100);
      digitalWrite ( open1, 0 );
    }

  } else {
    if (requestRangeValid == 1) {
      Serial.println ( "Invalid digest recieved." );
    }
  }

  char upTimeString[20];
  snprintf ( upTimeString, 20, "%02d:%02d:%02d", hr, min % 60, sec % 60) ; // 00:38:47 0123456789

  snprintf ( temp, 2000,

             "<html>\
  <head>\
    <meta http-equiv='refresh' content='%d; url=/'/>\
    <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\
    <title>Garage Door Opener</title>\
    <script src='externalScript.js'></script>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h2>Garage Door Opener</h1>\
    Sensor1: %d Sensor2: %d <br>\
    <form name=myForm method=get onsubmit=\"return validateForm()\" >\
    <input type=hidden name=time value=%d><br>\
    Password: <input type=password name=password value=><br>\
    <!-- Request Password (Computed in Javascript) : --><input type=hidden size=50 name=requestPassword>\
    <!-- Server Digest:  --><input type=hidden name=serverDigest value=%20s size=50>\
    <input type=submit value=Open>\
    </form>\
    <p>Uptime: %20s</p>\
  </body>\
</html>",

             requestTTL, digitalRead(sensor1), digitalRead(sensor2), sec, digestStringHex, upTimeString
           );

  server.send ( 200, "text/html", temp );
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

