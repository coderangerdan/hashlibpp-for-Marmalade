#include "s3e.h"
#include "iwgx.h"
#include "hashlibpp.h"
#include <string>

int main()
{
	// Set the string we want to hash
	std::string hashString = "Hash this value";

	// Hash our string
	hashwrapper *sha256 = new sha256wrapper();
	std::string sSHA256 = sha256->getHashFromString( hashString.c_str() );


	// Initialise the IwGx drawing module
	IwGxInit();

	// Set the background colour to grey
	IwGxSetColClear(0x88, 0x88, 0x88, 0);


	// Wait for a quit request from the host OS
	while (!s3eDeviceCheckQuitRequest())
	{
		// Clear the surface
		IwGxClear();

		// Use the built-in font to display the hash values
		IwGxPrintString(5, 140, hashString.c_str() );
		IwGxPrintString(5, 160, sSHA256.c_str() );

		// Standard EGL-style flush of drawing to the surface
		IwGxFlush();

		// Standard EGL-style flipping of double-buffers
		IwGxSwapBuffers();

		// Sleep for 0ms to allow the OS to process events etc.
		s3eDeviceYield(0);
	}

	// Shut down the IwGx drawing module
	IwGxTerminate();

	// Cleanup our hash wrapper
	if( sha256 )
	{
		delete sha256;
		sha256 = NULL;
	}

	return 0;
}
