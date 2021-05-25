# I2C Scanner

Simple Arduino library for scanning I2C bus for devices.

Inspiration taken from https://github.com/mcauser/i2cdetect and https://github.com/Ailme/i2c_scanner_platformio

Outputs a table similar to the [linux program](http://linux.die.net/man/8/i2cdetect) i2cdetect.

Each cell will contain one of the following symbols:

* "--" when the address was probed but no chip answered
* An address in hexadecimal, e.g. "1e", when a chip was found at the address
* For found device, the scanner will try to determine the device type and list it below the table

The optional parameters first and last restrict the scanning range (default: from 0x08 to 0x77).

## Example

```cpp
#include <Wire.h>
#include <i2cdetect.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  i2cdetect();  // default range from 0x08 to 0x77
  delay(5000);
}
```

## Serial monitor output

```
Scanning address range 0x08-0x77
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- 23 -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- 3c -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --

23: BH1750 brightness sensor
3c: SSD 1306 display
```

## Tested on devices

* [WeMos D1 mini - ESP8266](http://www.wemos.cc/wiki/doku.php?id=en:d1_mini)
