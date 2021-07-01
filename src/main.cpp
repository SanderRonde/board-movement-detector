#include <ArduinoOTA.h>
#include <movement.h>
#include <Arduino.h>
#include <config.h>
#include <telnet.h>
#include <ota.h>
#include <net.h>
#include <string.h>

void setup()
{
	Serial.begin(115200);
	Serial.println("Booting");

	// Setup telnet
	Telnet::setup((String("movement-detector-") + NAME).c_str());

	// Setup OTA and wait
	OTA::setup();
	LOGF("Reset reason = %s - %s\n", ESP.getResetReason().c_str());
	LOGN("Booted. Waiting for possible OTAs");
	OTA::wait_for_otas();
	LOGN("Stopped waiting");

	// Setup the rest
	Movement::setup();

	// Done
	LOGN("Booted");
}

void loop()
{
	OTA::loop();
	Telnet::loop();
	Movement::loop();
}
