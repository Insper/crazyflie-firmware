#include "mpu9250.h"
 
// Class constructor
MPU9250::MPU9250(PinName sda, PinName scl) : i2c(sda, scl)
{
}
 
// Initialize sensor (return true if connection succeeded)
bool MPU9250::init()
{
    // Setup I2C bus
    setup_i2c();
    // Test I2C bus
    if (test_i2c()) 
    {
        // Setup auxiliary I2C bus pins
        setup_aux_i2c();
        // Setup accelerometer and gyroscope
        setup_acc();
        setup_gyr();
        return true;
    } 
    else 
    {
        return false;
    }
}
 
// Read sensor data
void MPU9250::read()
{
    // Read accelerometer and gyroscope data
    read_acc();
    read_gyr();
}
 
// Write data into register on given I2C bus address
void MPU9250::write_reg(uint8_t add, uint8_t reg, uint8_t data)
{
    // Register address and data that will be writed
    char i2c_reg_data[2] = {reg, data};
    // Point to register address and write data
    i2c.write(add, i2c_reg_data, 2);
}
 
// Read data from register on given I2C bus address
char MPU9250::read_reg(uint8_t add, uint8_t reg)
{
    // Register address
    char i2c_reg[1] = {reg};
    // Data that will be readed
    char i2c_data[1];
    // Point to register address
    i2c.write(add, i2c_reg, 1);
    // Read data
    i2c.read(add, i2c_data, 1);
    // Return readed data
    return i2c_data[0];
}

// Setup I2C bus
void MPU9250::setup_i2c()
{
    // Setup I2C bus frequency to 100kHz
    i2c.frequency(100000);
}
 
// Test I2C bus
bool MPU9250::test_i2c()
{
    // Read device identity and check if it is equal to 0x71
    return (read_reg(MPU9250_ADDRESS, WHO_AM_I) == 0x71);
}
 
// Setup auxiliary I2C bus pins
void MPU9250::setup_aux_i2c()
{
    // Setup auxiliary I2C bus pins
    write_reg(MPU9250_ADDRESS, INT_PIN_CFG, 0b00000010);
}
 
// Setup accelerometer configurations (full-scale range)
void MPU9250::setup_acc(acc_range a_range)
{
    // Write configuration data
    write_reg(MPU9250_ADDRESS, ACC_CONFIG_1, (0b000 << 5) | (a_range << 3) | 0b000);
    // Adjust resolution [m/s^2 / bit] accordingly to choose scale (g)
    switch (a_range) 
    {
        case ACC_RANGE_2G:
            a_res =  2.0*(9.80665/32768.0);
            break;
        case ACC_RANGE_4G:
            a_res =  4.0*(9.80665/32768.0);
            break;
        case ACC_RANGE_8G:
            a_res =  8.0*(9.80665/32768.0);
            break;
        case ACC_RANGE_16G:
            a_res = 16.0*(9.80665/32768.0);
            break;
    }
}
 
// Setup gyroscope configurations (full-scale range)
void MPU9250::setup_gyr(gyr_range g_range)
{
    // Write configuration data
    write_reg(MPU9250_ADDRESS, GYR_CONFIG, (0b000 << 5) | (g_range << 3) | 0b000);
    // Adjust resolution [rad/s / bit] accordingly to choose scale
    switch (g_range) 
    {
        case GYR_RANGE_250DPS:
            g_res =  250.0*((3.14159/180.0)/32768.0);
            break;
        case GYR_RANGE_500DPS:
            g_res =  500.0*((3.14159/180.0)/32768.0);
            break;
        case GYR_RANGE_1000DPS:
            g_res = 1000.0*((3.14159/180.0)/32768.0);
            break;
        case GYR_RANGE_2000DPS:
            g_res = 2000.0*((3.14159/180.0)/32768.0);
            break;
    }
}
 
// Read accelerometer output data
void MPU9250::read_acc()
{
    // Register address
    char reg[1] = {ACC_XOUT_H};
    // Data that we're going to read
    char data[6];
    // Point to register address
    i2c.write(MPU9250_ADDRESS, reg, 1);
    // Read data from this address (register address will auto-increment and all three axis information (two 8 bit data each) will be read)
    i2c.read(MPU9250_ADDRESS, data, 6);
    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t ax_raw = (data[0] << 8 ) | data[1];
    int16_t ay_raw = (data[2] << 8 ) | data[3];
    int16_t az_raw = (data[4] << 8 ) | data[5];
    // Convert to SI units [m/s^2]
    ax =  ay_raw*a_res;
    ay = -ax_raw*a_res;
    az = -az_raw*a_res;
}
 
// Read gyroscope data
void MPU9250::read_gyr()
{
    // Register address
    char reg[1] = {GYR_XOUT_H};
    // Data that we're going to read
    char data[6];
    // Point to register address
    i2c.write(MPU9250_ADDRESS, reg, 1);
    // Read data from this address (register address will auto-increment and all three axis information (two 8 bit data each) will be read)
    i2c.read(MPU9250_ADDRESS, data, 6);
    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t gx_raw = (data[0] << 8 ) | data[1];
    int16_t gy_raw = (data[2] << 8 ) | data[3];
    int16_t gz_raw = (data[4] << 8 ) | data[5];
    // Convert to SI units [rad/s]
    gx = -gy_raw*g_res;
    gy =  gx_raw*g_res;
    gz =  gz_raw*g_res;
}