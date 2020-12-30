#pragma once

// When enabled, uses the digital pin (D1), when disabled,
// uses the analog pin (A0)
#define DIGITAL 1
// When enabled, takes any single HIGH result read as absolute
// truth that there is movement. When false, checks whether the
// value holds for the configured amount of MS before signaling
// movement
#define ABSOLUTE_READ 1

#define NAME "door"
#ifdef DIGITAL
#define IN_PIN D1
#else
#define IN_PIN A0
#endif