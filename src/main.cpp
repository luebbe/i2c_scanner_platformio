/*
   Wire - I2C Scanner

   The WeMos D1 Mini I2C bus uses pins:
   D1 = SCL
   D2 = SDA
*/

#include "i2cscan.h"

const int sclPin = D1;
const int sdaPin = D2;

void getName(int address);

void setup()
{
  Wire.begin(sdaPin, sclPin);

  Serial.begin(SERIAL_SPEED);

  Serial.println("I2C Scanner");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);
  i2cscan();
  digitalWrite(LED_BUILTIN, HIGH);

  delay(5000);
}