#include "lps25h.h"

/** Class constructor */
LPS25H::LPS25H(PinName sda, PinName scl) : i2c(sda, scl)
{
}

/** Init barometer */
bool LPS25H::init()
{
    // Setup I2C bus
    setup_i2c();

    // Test I2C bus
    if (test_i2c()) {
        // Setup accelerometer and gyroscope configurations
        setup_baro();
        return true;
    } else {
        return false;
    }
}
/** Read barometer */
void LPS25H::read()
{
    read_baro();
}

/** Setup barometer */
void LPS25H::setup_baro()
{
    //
    write_reg(CTRL_REG1, 0b10110000);
}


/** Setup I2C bus */
void LPS25H::setup_i2c()
{
    // Setup I2C bus frequency to 100kHz
    i2c.frequency(400000);
}

/** Test I2C bus */
bool LPS25H::test_i2c()
{
    // Read device identity
    uint8_t device_id = read_reg(WHO_AM_I);

    // Check if device identity is 0xBD
    if (device_id == 0xBD) {
        return true;
    } else {
        return false;
    }
}

/** Read barometer */
void LPS25H::read_baro()
{    
    // Read raw data (three 8 bit data)
    uint8_t p_raw_xl = read_reg(PRESS_OUT_XL);
    uint8_t p_raw_l = read_reg(PRESS_OUT_L);
    uint8_t p_raw_h = read_reg(PRESS_OUT_H);

    // Reassemble the data (one 24 bit data)
    int32_t p_raw = (p_raw_h << 16 ) | (p_raw_l << 8 ) | p_raw_xl;
    
    // Convert raw data to SI units [hPa]
    p = p_raw / 4096.0;
    
    // Calculate altitude [m] from pressure [hPa]
    z = 44330.8f*(1.0f-pow((p/1025.0f),0.190263f));
}

/** Write data into register on MPU9250 I2C bus address */
void LPS25H::write_reg(uint8_t reg, uint8_t data)
{
    // Register address and data that will be writed
    char i2c_reg_data[2] = {reg, data};

    // Point to register address and write data
    i2c.write(LPS25H_ADDRESS, i2c_reg_data, 2);
}

/** Read data from register on MPU9250 I2C bus address */
char LPS25H::read_reg(uint8_t reg)
{
    // Register address
    char i2c_reg[1] = {reg};
    // Data that will be readed
    char i2c_data[1];

    // Point to register address
    i2c.write(LPS25H_ADDRESS, i2c_reg, 1);
    // Read data
    i2c.read(LPS25H_ADDRESS, i2c_data, 1);

    // Return readed data
    return i2c_data[0];
}