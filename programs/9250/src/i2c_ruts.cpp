/*
 *  i2c_ruts.c
 *      Routines to use i2c bus
 */

#include <Arduino.h>
#include <Wire.h>

#include "i2c_ruts.h"

/*
 *  init_i2c_ruts
 *      Cold init for i2c access
 */

void
init_i2c_ruts( void )
{
    Wire.begin();       // setup of Wire object
}

/*  
 *  i2c_read:
 *      Read Nbytes bytes from I2C device at address Address.
 *      Put read bytes starting at register Register in the Data array.
 */

void
i2c_read(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t *Data)
{
    // Set register address
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.endTransmission();

    // Read Nbytes
    Wire.requestFrom(Address, Nbytes);
    uint8_t index = 0;
    while (Wire.available())
        Data[index++] = Wire.read();
}

/* 
 *  i2c_write_byte:
 *     Write a byte (Data) in device (Address) at register (Register)
 */

void
i2c_write_byte(uint8_t Address, uint8_t Register, uint8_t Data)
{
    // Set register address
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.write(Data);
    Wire.endTransmission();
}


