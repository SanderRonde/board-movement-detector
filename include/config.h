#pragma once

#define DIGITAL 1

#define NAME "mirror"
#ifdef DIGITAL
#define IN_PIN D1
#else
#define IN_PIN A0
#endif