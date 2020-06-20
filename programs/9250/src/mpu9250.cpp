/*
 *  mpu9250.cpp
 *      Routines for manage one MPU9250
 */

/*
 *  System includes
 */

#include <Arduino.h>

/*
 *  Project includes
 */

#include "mpu9250.h"
#include "i2c_ruts.h"

/*
 *  Registers from MPU9250
 */

#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

/*
 *  Public functions
 */

/*
 *  init_mpu9250:
 *      Inits all from cold start
 */

void
init_mpu9250( void )
{
    init_i2c_ruts();
}

/*
 *  setup_mpu9250:
 *      configures MPU9250 at I2C address
 */

void
setup_mpu9250( uint8_t address )
{
    // Set accelerometers low pass filter at 5Hz
    i2c_write_byte(address, 29, 0x06);
    // Set gyroscope low pass filter at 5Hz
    i2c_write_byte(address, 26, 0x06);

    i2c_write_byte(address, 27, GYRO_FULL_SCALE_1000_DPS);
    // Configure accelerometers range
    i2c_write_byte(address, 28, ACC_FULL_SCALE_4_G);
    // Set by pass mode for the magnetometers
    i2c_write_byte(address, 0x37, 0x02);
    // Request continuous magnetometer measurements in 16 bits
    i2c_write_byte(MAG_ADDRESS, 0x0A, 0x16);
}

/*
 *  data_mpu9250:
 *      Gets data fom MPU92150 at I2C address
 *      Results return in struct agmt_t pointed by p
 */

void
data_mpu9250( uint8_t address, agmt_t *p )
{
    unsigned char buffer[14], ST1_A;



    // Accelerometer and gyroscope data

    i2c_read(address, 0x3B, 14, buffer);

    // Create 16 bits values from 8 bits data

    // Accelerometer
    p->accel[X] = -(buffer[0] << 8 | buffer[1]);
    p->accel[Y] = -(buffer[2] << 8 | buffer[3]);
    p->accel[Z] =   buffer[4] << 8 | buffer[5];

    // Gyroscope
    p->gyro[X] =  -(buffer[8] << 8 | buffer[9]);
    p->gyro[Y] = -(buffer[10] << 8 | buffer[11]);
    p->gyro[Z] =   buffer[12] << 8 | buffer[13];


    /*
     *  Magnetometer
     */

    // Read register Status 1 and wait for the DRDY: Data Ready

    do
    {
        i2c_read(MAG_ADDRESS, 0x02, 1, &ST1_A);
    } while (!(ST1_A & 0x01));

    i2c_read(MAG_ADDRESS, 0x03, 7, buffer);

    // Create 16 bits values from 8 bits data

    p->magneto[X] = -(buffer[3] << 8 | buffer[2]) + 200;
    p->magneto[Y] = -(buffer[1] << 8 | buffer[0]) - 70;
    p->magneto[Z] = -(buffer[5] << 8 | buffer[4]) - 700;
}



