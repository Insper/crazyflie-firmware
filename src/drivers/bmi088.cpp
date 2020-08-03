#include "bmi088.h"
 
// Class constructor
BMI088::BMI088(PinName sda, PinName scl) : i2c(sda, scl)
{
    // Configure I2C frequency
    i2c.frequency(100000);
}
 
// Initialize sensor (return true if connection succeeded)
bool BMI088::init()
{
    // Read accelerometer and gyroscope device identity and check if they are equal to 0x1E and 0x0F
    if ((read_reg(ACC_ADD, ACC_CHIP_ID) == 0x1E) && (read_reg(GYR_ADD,GYR_CHIP_ID) == 0x0F))
    {
        // Initialize accelerometer and gyroscope
        init_acc();
        init_gyr();
        return true;
    } 
    else 
    {
        return false;
    }
}
 
// Read accelerometer and gyroscope data
void BMI088::read()
{
    read_acc();
    read_gyr();
}
 
// Initialize accelerometer
void BMI088::init_acc(acc_range a_range, acc_odr a_odr)
{
    // Configure full-scale range
    write_reg(ACC_ADD, ACC_RANGE, (0x00 << 2) | (a_range));
    // Configure output data rate
    write_reg(ACC_ADD, ACC_CONF, (0X0A << 4) | (a_odr));
    // Put it in active mode 
    write_reg(ACC_ADD, ACC_PWR_CTRL, 0x04);
    // Adjust resolution [m/s^2 / bit] according to choosed full-scale range
    switch (a_range) 
    {
        case ACC_RANGE_3G:
            a_res =  3.0*(9.80665/32768.0);
            break;
        case ACC_RANGE_6G:
            a_res =  6.0*(9.80665/32768.0);
            break;
        case ACC_RANGE_12G:
            a_res =  12.0*(9.80665/32768.0);
            break;
        case ACC_RANGE_24G:
            a_res = 24.0*(9.80665/32768.0);
            break;
    }
}
 
// Initialize gyroscope
void BMI088::init_gyr(gyr_range g_range, gyr_odr g_odr)
{
    // Configure full-scale range
    write_reg(GYR_ADD, GYR_RANGE, (0b000000 << 2) | (g_range));
    // Configure output data rate
    write_reg(GYR_ADD, GYR_BANDWIDTH, (0b100000 << 2) | (g_odr));
    // Adjust resolution [rad/s / bit] according to choosed full-scale range
    switch (g_range) 
    {
        case GYR_RANGE_125DPS:
            g_res =  125.0*((3.14159/180.0)/32768.0);
            break;
        case GYR_RANGE_250DPS:
            g_res =  250.0*((3.14159/180.0)/32768.0);
            break;
        case GYR_RANGE_500DPS:
            g_res = 500.0*((3.14159/180.0)/32768.0);
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
void BMI088::read_acc()
{
    // Register address
    char reg[1] = {ACC_X_LSB};
    // Data that will be readed
    char data[6];
    // Point to register address
    i2c.write(ACC_ADD, reg, 1);
    // Read data from this address (register address will auto-increment and all three axis information (two 8 bit data each) will be read)
    i2c.read(ACC_ADD, data, 6);
    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t ax_raw = data[0] | (data[1] << 8);
    int16_t ay_raw = data[2] | (data[3] << 8);
    int16_t az_raw = data[4] | (data[5] << 8);
    // Convert to SI units [m/s^2]
    ax = -ax_raw*a_res;
    ay = -ay_raw*a_res;
    az = -az_raw*a_res;
}
 
// Read gyroscope data
void BMI088::read_gyr()
{
    // Register address
    char reg[1] = {GYR_X_LSB};
    // Data that will be readed
    char data[6];
    // Point to register address
    i2c.write(GYR_ADD, reg, 1);
    // Read data from this address (register address will auto-increment and all three axis information (two 8 bit data each) will be read)
    i2c.read(GYR_ADD, data, 6);
    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t gx_raw = data[0] | (data[1] << 8);
    int16_t gy_raw = data[2] | (data[3] << 8);
    int16_t gz_raw = data[4] | (data[5] << 8);
    // Convert to SI units [rad/s]
    gx =  gx_raw*g_res;
    gy =  gy_raw*g_res;
    gz =  gz_raw*g_res;
}
 
// Read data from register on given I2C bus address
uint8_t BMI088::read_reg(uint8_t add, uint8_t reg)
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

// Write data into register on given I2C bus address
void BMI088::write_reg(uint8_t add, uint8_t reg, uint8_t data)
{
    // Register address and data that will be writed
    char i2c_reg_data[2] = {reg, data};
    // Point to register address and write data
    i2c.write(add, i2c_reg_data, 2);
}