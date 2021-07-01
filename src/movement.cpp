#include <movement.h>
#include <secrets.h>
#include <Arduino.h>
#include "lib-telnet.h"
#include <config.h>
#include "lib-net.h"

#define MOVEMENT_TIME 100
#define COOLDOWN_TIME 1000 * 3
#define MEASUREMENT_COOLDOWN 50

#define LOGGING_MODE 1

namespace Movement
{
	void setup()
	{
		pinMode(IN_PIN, INPUT);
	}

	void send_movement()
	{
		char *path = (char *)malloc(sizeof(char) * 40);
		sprintf(path, "/movement/%s", NAME);
		Net::req_auth(SECRET_KEY, BASE_NAME, 80, path);
		free(path);
	}

	int last_read = 0;
	bool is_movement()
	{
#ifdef DIGITAL
		return digitalRead(IN_PIN) == HIGH;
#else
		int current_read = analogRead(IN_PIN);
		#ifdef LOGGING_MODE
		if (current_read != last_read)
		{
			LOGF("Distance = %d mm\n", current_read);
			last_read = current_read;
		}
		#endif
#ifdef INCREASING_READS
		return current_read > MOVEMENT_MIN;
#else
		return current_read < MOVEMENT_MIN;
#endif
#endif
	}

	bool has_been_off = true;
	unsigned long last_log = millis();
	unsigned long movement_since = 0;
	unsigned long last_measurement = millis();
	void loop()
	{
		if (millis() - last_measurement <= MEASUREMENT_COOLDOWN)
			return;
		last_measurement = millis();

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