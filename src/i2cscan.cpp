/*
i2cscan.cpp - Arduino library for scanning I2C bus for devices
*/

#include "i2cscan.h"

// Adresses 0b0000XXX and 0b1111XXX are used for special purposes
const uint8_t cMinAddr = 0b0000111 + 1;
const uint8_t cMaxAddr = 0b1111000 - 1;

void getName(int address);

void i2cscan(uint8_t first, uint8_t last)
{
  uint8_t i, address, error;
  char buff[10];
  std::vector<uint8_t> devices;

  if (first < cMinAddr)
  {
    first = cMinAddr;
  }

  if (last > cMaxAddr)
  {
    last = cMaxAddr;
  }

  // table header
  Serial.printf("Scanning address range 0x%02x-0x%02x\n", first, last);
  Serial.print("   ");
  for (i = 0; i < 16; i++)
  {
    sprintf(buff, "%3x", i);
    Serial.print(buff);
  }

  // table body
  // addresses 0x00 through 0x77
  devices.clear();
  for (address = 0; address <= cMaxAddr; address++)
  {
    if (address % 16 == 0)
    {
      sprintf(buff, "\n%02x:", address & 0xF0);
      Serial.print(buff);
    }
    if (address >= first && address <= last)
    {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
      if (error == 0)
      {
        // device found
        devices.push_back(address);
        sprintf(buff, " %02x", address);
        Serial.print(buff);
      }
      else if (error == 4)
      {
        // other error
        Serial.print(" XX");
      }
      else
      {
        // error = 2: received NACK on transmit of address
        // error = 3: received NACK on transmit of data
        Serial.print(" --");
      }
    }
    else
    {
      // address not scanned
      Serial.print("   ");
    }
  }
  Serial.println("\n");

  for (uint8_t addr : devices)
  {
    getName(addr);
  }
  Serial.println("\n");
}

void i2cscan()
{
  i2cscan(cMinAddr, cMaxAddr); // default range.
}

void getName(int address)
{
  byte deviceId = 0;

  Serial.printf("%02x: ", address);

  switch (address)
  {
  case 0x1D:
    Serial.println("ADXL345 digital accelerometer");
    break;
  case 0x1E:
    Serial.println("HMC5883L 3-axis digital compass");
    break;
  // case 0x20:
  // case 0x21:
  // case 0x22:
  case 0x23:
    Serial.println("BH1750 brightness sensor");
    break;
  // case 0x24:
  // case 0x25:
  case 0x26:
    Serial.println("PCF8574 I/O expander");
    break;
  case 0x27:
    Serial.println("LCD with I2C backpack");
    Serial.println("PCF8574 I/O expander");
    break;
  // case 0x38:
  // case 0x39:
  // case 0x3A:
  // case 0x3B:
  case 0x3C:
    Serial.println("SSD 1306 display");
    break;
  // case 0x3D:
  case 0x3E:
    Serial.println("PCF8574A I/O expander");
    break;
  case 0x3F:
    Serial.println("LCD with I2C backpack");
    Serial.println("PCF8574A I/O expander");
    break;
  case 0x40:
    Serial.println("HTU21D digital humidity and temperature sensor");
    break;
  // case 0x48:
  // case 0x49:
  // case 0x4A:
  case 0x4B:
    Serial.println("ADS1113, ADS1114, ADS1115, ADS1013, ADS1014, ADS1015");
    break;
  // case 0x50:
  // case 0x51:
  // case 0x52:
  // case 0x54:
  // case 0x55:
  // case 0x56:
  case 0x57:
    Serial.println("AT24C32/64 Eeprom family");
    break;
  case 0x53:
    Serial.println("ADXL345 digital accelerometer");
    Serial.println("or AT24C32/64 Eeprom family");
  case 0x68:
    Serial.println("DS3231 or DS1307 Real Time Clock");
    Serial.println("or MPU9250 gyroscope, accelerometer, magnetometer");
    Serial.println("or L3G4200D gyroscope");
    break;
  case 0x69: // same device also on 0x68
             // also need to study pass-through mode of MPU9250
    Serial.println("MPU9250 gyroscope, accelerometer, magnetometer");
    Serial.println("or L3G4200D gyroscope");
    break;
  case 0x76:
  case 0x77:
    Serial.println("BMP280 or BME280 or BME680 or MS5607,MS5611,MS5637");
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
      deviceId = Wire.read();
    } // end of if (Wire.available() == 3)

    Serial.print("Device ID=");
    Serial.print(deviceId, HEX);

    if (deviceId == 0x58)
      Serial.println("= BMP280");
    else if (deviceId == 0x60)
      Serial.println("= BME280");
    else if (deviceId == 0x61)
      Serial.println("= BME680");
    else
      Serial.println("ID not in list");
    break;
  default:
    Serial.println("device not in list");
    break;
  }
}
