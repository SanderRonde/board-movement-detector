#include "lib-includes.h"
#include "lib-telnet.h"
#include "movement.h"
#include "lib-main.h"
#include "lib-ota.h"
#include "secrets.h"
#include "string.h"
#include "config.h"

void setup()
{
	Main::connect((String("movement-detector-") + NAME).c_str(), OTA_PW, WIFI_SSID, WIFI_PW);
	Movement::setup();
	Main::connect_done();
}

void loop()
{
	OTA::loop();
	Telnet::loop();
	Movement::loop();
}
