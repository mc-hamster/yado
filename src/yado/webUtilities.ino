
void computeServerDigest( int sec, char  digestStringHex[]) {

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

