/*
   Wire - I2C Scanner

   The WeMos D1 Mini I2C bus uses pins:
   D1 = SCL
   D2 = SDA
*/

#include <Arduino.h>
#include <Wire.h>

const int sclPin = D1;
const int sdaPin = D2;

void getName(int address);

void setup()
{
  Wire.begin(sdaPin, sclPin);

  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("I2C Scanner");
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop()
{
  byte error, address;
  int nDevices;

  digitalWrite(BUILTIN_LED, LOW);

  Serial.println("Scanning...");

  nDevices = 0;
  Wire.endTransmission();
  for (address = 1; address < 128; address++)
  {
    // The i2c scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");

      if (address < 16)
        Serial.print("0");

      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;

      getName(address);
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");

      if (address < 16)
        Serial.print("0");

      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("Done.\n");
  }

  digitalWrite(BUILTIN_LED, HIGH);
  delay(5000);
}

void getName(int address)
{
  byte data1 = 0;
  byte error1 = 0;

  switch (address)
  {
  case 0x1D:
    Serial.println(" ADXL345 digital accelerometer");
    break;
  case 0x1E:
    Serial.println(" HMC5883L 3-axis digital compass");
    break;
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
    Serial.println(" PCF8574 I/O expander");
    break;
  case 0x27:
    Serial.println(" LCD with I2C backpack");
    Serial.println(" PCF8574 I/O expander");
    break;
  case 0x38:
  case 0x39:
  case 0x3A:
  case 0x3B:
  case 0x3C:
  case 0x3D:
  case 0x3E:
    Serial.println(" PCF8574A I/O expander");
    break;
  case 0x3F:
    Serial.println(" LCD with I2C backpack");
    Serial.println(" PCF8574A I/O expander");
    break;
  case 0x40:
    Serial.println(" HTU21D digital humidity and temperature sensor");
    break;
  case 0x48:
  case 0x49:
  case 0x4A:
  case 0x4B:
    Serial.println(" ADS1113, ADS1114, ADS1115, ADS1013, ADS1014, ADS1015");
    break;
  case 0x50:
  case 0x51:
  case 0x52:
  case 0x54:
  case 0x55:
  case 0x56:
  case 0x57:
    Serial.println(" AT24C32/64 Eeprom family");
    break;
  case 0x53:
    Serial.println(" ADXL345 digital accelerometer");
    Serial.println(" or AT24C32/64 Eeprom family");
  case 0x68:
    Serial.println(" DS3231 or DS1307 Real Time Clock");
    Serial.println(" or MPU9250 gyroscope, accelerometer, magnetometer");
    Serial.println(" or L3G4200D gyroscope");
    break;
  case 0x69: // same device also on 0x68
             // also need to study pass-through mode of MPU9250
    Serial.println(" MPU9250 gyroscope, accelerometer, magnetometer");
    Serial.println(" or L3G4200D gyroscope");
    break;
  case 0x76:
  case 0x77:
    Serial.println(" BMP280 or BME280 or BME680 or MS5607,MS5611,MS5637");
    // note: address 0x77 may be BMP085,BMA180 and may not be MS5607 or MS5637 CHECK
    Wire.beginTransmission(address);
    // Select register
    Wire.write(0xD0); // 0xD0 hex address of chip_id
    // Stop I2C Transmission
    Wire.endTransmission();
    // Request 1 bytes of data
    Wire.requestFrom(address, 1);
    // Read 1 byte of data
    if (Wire.available() == 1)
    {
      data1 = Wire.read();
    } // end of if (Wire.available() == 3)

    Serial.print("Device ID=");
    Serial.print(data1, HEX);

    if (data1 == 0x58)
      Serial.println(" = BMP280");
    else if (data1 == 0x60)
      Serial.println(" = BME280");
    else if (data1 == 0x61)
      Serial.println(" = BME680");
    else
      Serial.println(" ID not in list");
    break;
  default:
    Serial.println("device not in list");
    break;
  }
}