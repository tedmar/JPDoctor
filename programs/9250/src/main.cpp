/*
 *  Project: dual-9250 - file: main.cpp
 *  Universidad Austral - June 16, 2020
 *  HFerrari - EAMartinez
 *
 *  Setup and shows data of up to two MPU9250
 */

/*
 *  System includes
 */

#include <Arduino.h>
#include <string.h>

/*
 *  Project includes
 */

#include "mpu9250.h"

/*
 *  types
 */

typedef struct
{
    unsigned i2c_add;
    char *name_9250;
} dev9250_t;

/*
 *  MPU9250 definitions
 */

static const dev9250_t dev1 =
{
    0x68, (char *)"A"
};

static const dev9250_t dev2 =
{
    0x69, (char *)"B"
};

/*
 *  Static variables
 */

static unsigned long ti;    //  Measures seconds from start running

/*
 *  Static functions
 */

static void
dims_print( int16_t magn[] )
{
    Serial.printf( "[%6d,%6d,%6d] ", magn[X], magn[Y], magn[Z] );
}

/*
 *  process_mpu9250:
 *      Receives:
 *          sensor_name for printing
 *          i2c address
 *      Get mpu9250 data and prints it
 */

static void
process_mpu9250(char *sensor_name, uint8_t address)
{
    agmt_t agmt;

    data_mpu9250( address, &agmt );

    Serial.printf( "{%s}[%8lu]: ", sensor_name, millis()-ti );
    dims_print( agmt.accel );
    dims_print( agmt.gyro );
    dims_print( agmt.magneto );
    Serial.println();
}


/*
 *  Startup function
 */

void
setup( void )
{
    Serial.begin(SERIAL_BAUD);

    init_mpu9250();
    setup_mpu9250(dev1.i2c_add);
    setup_mpu9250(dev1.i2c_add); 

    ti = millis();      //  Start time
}

/*  
 *  Main loop, read and display data
 */

void
loop( void )
{
    process_mpu9250(dev1.name_9250,dev1.i2c_add ); 
    process_mpu9250(dev2.name_9250,dev2.i2c_add ); 

    Serial.println();

    delay(READ_DELAY);
}
