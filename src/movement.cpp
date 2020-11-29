#pragma once

#include <secrets.h>
#include <Arduino.h>
#include <config.h>
#include <net.h>

#define COOLDOWN_PERIOD 1000 * 10

namespace Movement
{
	void setup()
	{
		pinMode(MOVEMENT_PIN, INPUT);
	}

	bool has_movement()
	{
		return digitalRead(MOVEMENT_PIN);
	}

	void notify_movement()
	{
		char *path = (char *)malloc(sizeof(char) * 40);
		sprintf(path, "/movement/%s", NAME);
		Net::req_auth(BASE_NAME, 80, path);
		free(path);
	}

	unsigned long last_movement = 0;
	void loop()
	{
		if (has_movement())
		{
			if (millis() > (last_movement + COOLDOWN_PERIOD))
			{
				notify_movement();
				last_movement = millis();
			}
		}
	}
} // namespace Movement