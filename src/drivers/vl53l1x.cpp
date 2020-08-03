#include "vl53l1x.h"
 
// Class constructor
VL53L1X::VL53L1X(PinName sda, PinName scl) : i2c(sda, scl)
{
    // Configure I2C frequency to 100kHz
    i2c.frequency(100000);
}
 
// Initialize sensor (return true if connection succeeded)
bool VL53L1X::init()
{
    // Read device identity and check if it is equal to 0xEACC
    if (read_reg16(VL53L1X_ADD,VL53L1X_ID) == 0xEACC)
    {
        // Set default configurations
        for (int i = 0; i<91; i++)
        {
            write_reg(VL53L1X_ADD, default_reg[i], default_data[i]);
        }
        // Set timming buget to 20ms
        write_reg16(VL53L1X_ADD, VL53L1_RANGE_CONFIG__TIMEOUT_MACROP_A_HI,0x001E);
		write_reg16(VL53L1X_ADD, VL53L1_RANGE_CONFIG__TIMEOUT_MACROP_B_HI,0x0022);
        // Set intermeasurement period to 20ms
        uint32_t imp = 20;
	    uint16_t clck = read_reg16(VL53L1X_ADD, VL53L1_RESULT__OSC_CALIBRATE_VAL) & 0x3FF;
	    write_reg32(VL53L1X_ADD, VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD, (uint32_t)(clck * imp * 1.075));
        return true;
    }
    else 
    {
        return false;
    }
}
 
// Read range data
void VL53L1X::read()
{
    d = read_reg16(VL53L1X_ADD,VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0)/1000.0;
}
 
// Read data from register of given device in I2C bus
uint8_t VL53L1X::read_reg(uint8_t dev, uint16_t reg)
{
    // Register address
    char reg_[2];
    reg_[0] = (reg >> 8) & 0xFF;
    reg_[1] =  reg       & 0xFF;
    // Data that will be readed
    char data[1];
    // Point to register address
    i2c.write(dev, reg_, 2);
    // Read data
    i2c.read(dev, data, 1);
    // Return readed data
    return data[0];
}

// Read data from register of given device in I2C bus
uint16_t VL53L1X::read_reg16(uint8_t dev, uint16_t reg)
{
    // Register address
    char reg_[2];
    reg_[0] = (reg >> 8) & 0xFF;
    reg_[1] =  reg       & 0xFF;
    // Data that will be readed
    char data[2];
    // Point to register address
    i2c.write(dev, reg_, 2);
    // Read data
    i2c.read(dev, data, 2);
    // Return readed data
    return (data[0] << 8) | data[1];
}

// Read data from register of given device in I2C bus
uint32_t VL53L1X::read_reg32(uint8_t dev, uint16_t reg)
{
    // Register address
    char reg_[2];
    reg_[0] = (reg >> 8) & 0xFF;
    reg_[1] =  reg       & 0xFF;
    // Data that will be readed
    char data[4];
    // Point to register address
    i2c.write(dev, reg_, 2);
    // Read data
    i2c.read(dev, data, 4);
    // Return readed data
    return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}

// Write data into register of given device in I2C
void VL53L1X::write_reg(uint8_t dev, uint16_t reg, uint8_t data)
{
    // Register address and data that will be writed
    char reg_data[3];
    reg_data[0] = (reg >> 8) & 0xFF;
    reg_data[1] =  reg       & 0xFF;
    reg_data[2] =  data      & 0xFF;
    // Point to register address and write data
    i2c.write(dev, reg_data, 3);
}

// Write data into register of given device in I2C
void VL53L1X::write_reg16(uint8_t dev, uint16_t reg, uint16_t data)
{
    // Register address and data that will be writed
    char reg_data[4];
    reg_data[0] = (reg >> 8)  & 0xFF;
    reg_data[1] =  reg        & 0xFF;
    reg_data[2] = (data >> 8) & 0xFF;
    reg_data[3] =  data       & 0xFF;
    // Point to register address and write data
    i2c.write(dev, reg_data, 4);
}

// Write data into register of given device in I2C
void VL53L1X::write_reg32(uint8_t dev, uint16_t reg, uint32_t data)
{
    // Register address and data that will be writed
    char reg_data[6];
    reg_data[0] = (reg >> 8)   & 0xFF;
    reg_data[1] =  reg         & 0xFF;
    reg_data[2] = (data >> 24) & 0xFF;
    reg_data[3] = (data >> 16) & 0xFF;
    reg_data[4] = (data >> 8)  & 0xFF;
    reg_data[5] =  data        & 0xFF;
    // Point to register address and write data
    i2c.write(dev, reg_data, 6);
}