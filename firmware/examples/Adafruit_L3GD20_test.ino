/***************************************************
  This is an example for the Adafruit Triple-Axis Gyro sensor

  Designed specifically to work with the Adafruit L3GD20 Breakout
  ----> https://www.adafruit.com/products/1032

  These sensors use I2C or SPI to communicate, 2 pins (I2C)
  or 4 pins (SPI) are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Kevin "KTOWN" Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_L3GD20/Adafruit_L3GD20.h"

// Comment this next line to use SPI
//#define USE_I2C

#ifdef USE_I2C
  // The default constructor uses I2C
  Adafruit_L3GD20 gyro;
#else
  // To use SPI, you have to define the pins
  #define GYRO_CS 4 // labeled CS
  #define GYRO_DO 5 // labeled SA0
  #define GYRO_DI 6  // labeled SDA
  #define GYRO_CLK 7 // labeled SCL
  Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif

bool gyro_initialized = false;
unsigned long old_time = 0;

void setup()
{
  // Try to initialise and warn if we couldn't detect the chip
   if (gyro.begin(gyro.L3DS20_RANGE_250DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    gyro_initialized = true;
  }
  else
  {
    Particle.publish("Error initializing gyro", PRIVATE);
  }
}

void loop()
{
  if(gyro_initialized && (millis() - old_time > 5000)) {
    gyro.read();
    Particle.publish("Data",
    "x: " + String(gyro.data.x) +
    " y: " + String(gyro.data.y) +
    " z: " + String(gyro.data.z),PRIVATE);
    old_time = millis();
    }
}
