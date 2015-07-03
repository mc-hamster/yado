
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

	char serverDigestHex[41];       // Without secret
	uint8_t serverDigestSecret[20]; // With secret
	char serverDigestSecretHex[41]; // With secret

	String preDigest = "";

	computeServerDigest(timeFromClient, serverDigestHex);

	preDigest = access;
	preDigest += serverDigestHex;
	
	sha1(preDigest, &serverDigestSecret[0]);
	
	
	// Convert array of decimal into array of ascii hex values
	for (int i = 0; i < 20; i++) {
		sprintf(&serverDigestSecretHex[i * 2], "%02x", serverDigestSecret[i]);
	}

	if (String(serverDigestSecretHex) == digestFromClient) {
		return true;
	} else {
	    return false;
	}
}

