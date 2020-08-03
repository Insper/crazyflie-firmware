#ifndef bmi088_h
#define bmi088_h
 
#include "mbed.h"
 
// Accelerometer I2C bus address (shift 1 bit left because mbed utilizes 8-bit addresses and not 7-bit)
#define ACC_ADD       0b0011000 << 1  
// Accelerometer device identity register address 
#define ACC_CHIP_ID   0x00
// Accelerometer configuration registers addresses
#define ACC_CONF      0x40
#define ACC_RANGE     0x41
#define ACC_PWR_CTRL  0x7D
// Accerometer data register addresses
#define ACC_X_LSB     0x12
#define ACC_X_MSB     0x13
#define ACC_Y_LSB     0x14
#define ACC_Y_MSB     0x15
#define ACC_Z_LSB     0x16
#define ACC_Z_MSB     0x17

// Gyroscope I2C bus address  (shift 1 bit left because mbed utilizes 8-bit addresses and not 7-bit)
#define GYR_ADD       0b1101001 << 1  
// Gyroscope device identity  
#define GYR_CHIP_ID   0x00
// Gyroscope configuration registers addresses
#define GYR_RANGE     0x0F
#define GYR_BANDWIDTH 0x10
// Gyroscope data register addresses
#define GYR_X_LSB     0x02
#define GYR_X_MSB     0x03
#define GYR_Y_LSB     0x04
#define GYR_Y_MSB     0x05
#define GYR_Z_LSB     0x06
#define GYR_Z_MSB     0x07
 
// Accelerometer full-scale ranges
enum acc_range
{
    ACC_RANGE_3G  = 0x00, 
    ACC_RANGE_6G  = 0x01,
    ACC_RANGE_12G = 0x02, 
    ACC_RANGE_24G = 0x03 
};

// Accelerometer output data rates
enum acc_odr
{
    ACC_ODR_12   = 0x05, 
    ACC_ODR_25   = 0x06, 
    ACC_ODR_50   = 0x07, 
    ACC_ODR_100  = 0x08, 
    ACC_ODR_200  = 0x09, 
    ACC_ODR_400  = 0x0A, 
    ACC_ODR_800  = 0x0B, 
    ACC_ODR_1600 = 0x0C, 
};
 
// Gyroscope full-scale ranges
enum gyr_range
{
    GYR_RANGE_2000DPS = 0x00,
    GYR_RANGE_1000DPS = 0x01,   
    GYR_RANGE_500DPS  = 0x02,   
    GYR_RANGE_250DPS  = 0x03,  
    GYR_RANGE_125DPS  = 0x04, 
};

// Gyroscope output data rates
enum gyr_odr
{
    GYR_ODR_2000 = 0x01, 
    GYR_ODR_1000 = 0x02, 
    GYR_ODR_400  = 0x03, 
    GYR_ODR_200  = 0x04, 
    GYR_ODR_100  = 0x05, 
};
 
// BMI088 (IMU sensor) class
class BMI088
{
    public:
        // Class constructor
        BMI088(PinName sda, PinName scl);
        // Initialize sensor
        bool init();
        // Read accelerometer and gyroscope data
        void read();
        // Accelerometer data in x, y and z axis [m/s^2]
        float ax, ay, az;
        // Gyroscope data in x, y and z axis [rad/s]
        float gx, gy, gz;
    private:     
        // Initialize accelerometer
        void init_acc(acc_range a_scale = ACC_RANGE_12G, acc_odr a_odr = ACC_ODR_100);
        // Initialize gyroscope
        void init_gyr(gyr_range g_scale = GYR_RANGE_500DPS, gyr_odr g_odr = GYR_ODR_2000);
        // Read accelerometer data
        void read_acc();
        // Read gyroscope data
        void read_gyr();          
        // Accelerometer resolution [m/s^2 / bit]
        float a_res;
        // Gyroscope resolution [rad/s / bit]
        float g_res;
        // I2C bus
        I2C i2c;  
        // Read data from register on given I2C bus address
        uint8_t read_reg(uint8_t add, uint8_t reg);      
        // Write data into register on given I2C bus address
        void write_reg(uint8_t add, uint8_t reg, uint8_t data);
        
};
 
#endif