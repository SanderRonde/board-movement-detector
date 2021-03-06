#include <movement.h>
#include <secrets.h>
#include <Arduino.h>
#include <telnet.h>
#include <config.h>
#include <net.h>

#define MOVEMENT_TIME 100
#define MOVEMENT_MIN 600
#define COOLDOWN_TIME 1000 * 3

namespace Movement
{
	void setup()
	{
#ifndef DIGITAL
		pinMode(IN_PIN, INPUT_PULLUP);
		digitalWrite(IN_PIN, HIGH);
#else
		pinMode(IN_PIN, INPUT);
#endif
	}

	void send_movement()
	{
		char *path = (char *)malloc(sizeof(char) * 40);
		sprintf(path, "/movement/%s", NAME);
		Net::req_auth(BASE_NAME, 80, path);
		free(path);
	}

	bool is_movement()
	{
#ifdef DIGITAL
		return digitalRead(IN_PIN) == HIGH;
#else
		return analogRead(IN_PIN) > MOVEMENT_MIN;
#endif
	}

	bool has_been_off = true;
	unsigned long last_log = millis();
	unsigned long movement_since = 0;
	void loop()
	{
		bool movement = is_movement();
		if (movement)
		{
			if (has_been_off && millis() - last_log >= COOLDOWN_TIME)
			{
#ifndef ABSOLUTE_READ
				if (movement_since != 0 && millis() - movement_since >= MOVEMENT_TIME)
				{
#endif
					send_movement();
					LOGN("Detected movement");
					has_been_off = false;
					last_log = millis();
#ifndef ABSOLUTE_READ
					movement_since = 0;
				}
				else if (movement_since == 0)
				{
					movement_since = millis();
				}
#endif
			}
		}
		else
		{
			has_been_off = true;
			movement_since = 0;
		}
	} // namespace Movement
} // namespace Movement