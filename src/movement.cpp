#include <movement.h>
#include <secrets.h>
#include <Arduino.h>
#include <telnet.h>
#include <config.h>
#include <net.h>

#define COOLDOWN_PERIOD 1000 * 10
#define PING_TIME 100

namespace Movement
{
	void setup()
	{
		pinMode(IN_PIN, INPUT_PULLUP);
		digitalWrite(IN_PIN, HIGH);
	}

	void send_movement()
	{
		char *path = (char *)malloc(sizeof(char) * 40);
		sprintf(path, "/movement/%s", NAME);
		Net::req_auth(BASE_NAME, 80, path);
		free(path);
	}

	bool is_movement(int movement_read)
	{
		return movement_read > 600;
	}

	unsigned int last_run = millis();
	unsigned int last_log = millis();
	void loop()
	{
		if (millis() - last_run >= PING_TIME)
		{
			last_run = millis();

			int movement_read = analogRead(IN_PIN);
			if (is_movement(movement_read) && millis() - last_log >= COOLDOWN_PERIOD)
			{
				LOGF("Logging movement %s - %d\n", NAME, movement_read);
				send_movement();
				last_log = millis();
			}
		}
	}
} // namespace Movement