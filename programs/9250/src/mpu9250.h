/*
 *  mpu9250.h
 *      Routines for manage one MPU9250
 */

enum                // Dimensions of each device in chip
{
    X, Y, Z,
    DIMS
};

typedef struct      //  Type for save magnitudes
{
    int16_t accel[DIMS];
    int16_t gyro[DIMS];
    int16_t magneto[DIMS];
    int16_t temperature;
} agmt_t;

/*
 *  init_mpu9250:
 *      Inits all from cold start
 */

void init_mpu9250( void );

/*
 *  setup_mpu9250:
 *      configures MPU9250 at I2C address
 */

void setup_mpu9250( uint8_t address );

/*
 *  data_mpu9250:
 *      Gets data fom MPU92150 at I2C address
 *      Results return in struct agmt_t pointed by p
 */

void data_mpu9250( uint8_t address, agmt_t *p );



