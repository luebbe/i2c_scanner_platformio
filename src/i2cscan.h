/*
i2cdetect.h - Arduino library for scanning I2C bus for devices
*/

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Wire.h"

void i2cscan(uint8_t first, uint8_t last);
void i2cscan();
