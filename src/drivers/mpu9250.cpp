#include "mpu9250.h"
 
/** Class constructor */
MPU9250::MPU9250(PinName sda, PinName scl) : i2c(sda, scl)
{
}
 
/** Try to initialize sensor (return true if succeed and false if failed) */
bool MPU9250::init()
{
    // Setup I2C bus
    setup_i2c();
 
    // Test I2C bus
    if (test_i2c()) {
        // Setup accelerometer and gyroscope configurations
        setup_accel();
        setup_gyro();
        // Setup auxiliary I2C bus pins
        setup_aux_i2c();
        return true;
    } else {
        return false;
    }
}
 
/** Read sensor data */
void MPU9250::read()
{
    // Read accelerometer and gyroscope data
    read_accel();
    read_gyro();
}
 
/** Setup I2C bus */
void MPU9250::setup_i2c()
{
    // Setup I2C bus frequency to 100kHz
    i2c.frequency(100000);
}
 
/** Test I2C bus */
bool MPU9250::test_i2c()
{
    // Read device identity
    uint8_t device_id = read_reg(WHO_AM_I);
 
    // Check if device identity is 0x71
    if (device_id == 0x71) {
        return true;
    } else {
        return false;
    }
}
 
/** Setup auxiliary I2C bus pins */
void MPU9250::setup_aux_i2c()
{
    // Write 
    write_reg(INT_PIN_CFG, 0b00000010);
}
 
/** Setup accelerometer configurations (full-scale range) */
void MPU9250::setup_accel(accel_scale a_scale)
{
    // Write configuration data
    write_reg(ACCEL_CONFIG_1, (0b000 << 5) | (a_scale << 3) | 0b000);
 
    // Adjust resolution [m/s^2 / bit] accordingly to choose scale (g)
    switch (a_scale) {
        case ACCEL_SCALE_2G:
            a_res = (2.0f*GRAVITY)/32768.0f;
            break;
        case ACCEL_SCALE_4G:
            a_res = (4.0f*GRAVITY)/32768.0f;
            break;
        case ACCEL_SCALE_8G:
            a_res = (8.0f*GRAVITY)/32768.0f;
            break;
        case ACCEL_SCALE_16G:
            a_res = (16.0f*GRAVITY)/32768.0f;
            break;
    }
}
 
/** Setup gyroscope configurations (full-scale range) */
void MPU9250::setup_gyro(gyro_scale g_scale)
{
    // Write configuration data
    write_reg(GYRO_CONFIG, (0b000 << 5) | (g_scale << 3) | 0b000);
 
    // Adjust resolution [rad/s / bit] accordingly to choose scale
    switch (g_scale) {
        case GYRO_SCALE_250DPS:
            g_res = (250.0f*(PI/180.0f))/32768.0f;
            break;
        case GYRO_SCALE_500DPS:
            g_res = (500.0f*(PI/180.0f))/32768.0f;
            break;
        case GYRO_SCALE_1000DPS:
            g_res = (1000.0f*(PI/180.0f))/32768.0f;
            break;
        case GYRO_SCALE_2000DPS:
            g_res = (2000.0f*(PI/180.0f))/32768.0f;
            break;
    }
}
 
/** Read accelerometer output data */
void MPU9250::read_accel()
{
    /*
    // Read raw data (two 8 bit data for each axis)
    uint8_t ax_raw_h = read_reg(ACCEL_XOUT_H);
    uint8_t ax_raw_l = read_reg(ACCEL_XOUT_L);
    uint8_t ay_raw_h = read_reg(ACCEL_YOUT_H);
    uint8_t ay_raw_l = read_reg(ACCEL_YOUT_L);
    uint8_t az_raw_h = read_reg(ACCEL_ZOUT_H);
    uint8_t az_raw_l = read_reg(ACCEL_ZOUT_L);
 
    // Reassemble raw data (one 16 bit data for each axis)
    int16_t ax_raw = (ax_raw_h << 8) | ax_raw_l;
    int16_t ay_raw = (ay_raw_h << 8) | ay_raw_l;
    int16_t az_raw = (az_raw_h << 8) | az_raw_l;
 
    // Convert raw data to SI units [m/s^2] and also convert from sensor reference frame to drone reference frame
    ax = ay_raw * a_res;
    ay = -ax_raw * a_res;
    az = -az_raw * a_res;
    */
    
    // MPU9250 I2C bus address
    char address = MPU9250_ADDRESS;
    // Register address
    char reg[1] = {ACCEL_XOUT_H};
    // Data that we're going to read
    char data[6];
 
    // Point to register address
    i2c.write(address, reg, 1);
    // Read data from this address (register address will auto-increment and all three axis information (two 8 bit data each) will be read)
    i2c.read(address, data, 6);
 
    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t ax_raw = (data[0] << 8 ) | data[1];
    int16_t ay_raw = (data[2] << 8 ) | data[3];
    int16_t az_raw = (data[4] << 8 ) | data[5];
    // Convert to SI units [m/s^2]
    ax = ay_raw * a_res;
    ay = -ax_raw * a_res;
    az = -az_raw * a_res;
}
 
/** Read accelerometer data */
void MPU9250::read_gyro()
{
    /*
    // Read raw data (two 8 bit data for each axis)
    uint8_t gx_raw_h = read_reg(GYRO_XOUT_H);
    uint8_t gx_raw_l = read_reg(GYRO_XOUT_L);
    uint8_t gy_raw_h = read_reg(GYRO_YOUT_H);
    uint8_t gy_raw_l = read_reg(GYRO_YOUT_L);
    uint8_t gz_raw_h = read_reg(GYRO_ZOUT_H);
    uint8_t gz_raw_l = read_reg(GYRO_ZOUT_L);
 
    // Reassemble raw data (one 16 bit data for each axis)
    int16_t gx_raw = (gx_raw_h << 8 ) | gx_raw_l;
    int16_t gy_raw = (gy_raw_h << 8 ) | gy_raw_l;
    int16_t gz_raw = (gz_raw_h << 8 ) | gz_raw_l;
 
    // Convert raw data to SI units [rad/s] and also convert from sensor reference frame to drone reference frame
    gx = -gy_raw * g_res;
    gy = gx_raw * g_res;
    gz = gz_raw * g_res;
    */
    // MPU9250 I2C bus address
    char address = MPU9250_ADDRESS;
    // Register address
    char reg[1] = {GYRO_XOUT_H};
    // Data that we're going to read
    char data[6];
 
    // Point to register address
    i2c.write(address, reg, 1);
    // Read data from this address (register address will auto-increment and all three axis information (two 8 bit data each) will be read)
    i2c.read(address, data, 6);
 
    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t gx_raw = (data[0] << 8 ) | data[1];
    int16_t gy_raw = (data[2] << 8 ) | data[3];
    int16_t gz_raw = (data[4] << 8 ) | data[5];
    // Convert to SI units [rad/s]
    gx = -gy_raw * g_res;
    gy = gx_raw * g_res;
    gz = gz_raw * g_res;
}
 
/** Write data into register on MPU9250 I2C bus address */
void MPU9250::write_reg(uint8_t reg, uint8_t data)
{
    // Register address and data that will be writed
    char i2c_reg_data[2] = {reg, data};
 
    // Point to register address and write data
    i2c.write(MPU9250_ADDRESS, i2c_reg_data, 2);
}
 
/** Read data from register on MPU9250 I2C bus address */
char MPU9250::read_reg(uint8_t reg)
{
    // Register address
    char i2c_reg[1] = {reg};
    // Data that will be readed
    char i2c_data[1];
 
    // Point to register address
    i2c.write(MPU9250_ADDRESS, i2c_reg, 1);
    // Read data
    i2c.read(MPU9250_ADDRESS, i2c_data, 1);
 
    // Return readed data
    return i2c_data[0];
}