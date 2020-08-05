#include "pmw3901.h"

// Class constructor
PMW3901::PMW3901(PinName mosi, PinName miso, PinName sclk, PinName csel) : spi(mosi, miso, sclk), cs(csel)
{
    // Deselect the device by seting chip select high
    cs = 1;
    // Configure SPI format for 8 bit data and mode 3 (high steady state clock and second edge capture)
    spi.format(8,3);
    // Configure SPI frequency to 2MHz
    spi.frequency(2000000);
}
    
// Initialize  sensor (return true if connection succeeded)
bool PMW3901::init()
{
    // Read device identity and check if it is equal to 0x49
    if (read_reg(PMW3901_ID) == 0x49)
    {
        // Set default configurations
        for (int i = 0; i<79; i++)
        {
            write_reg(PMW3901_DEFAULT_CONFIG_REG[i], PMW3901_DEFAULT_CONFIG_DATA[i]);
            if (i == 64)
            {
                wait(0.1);
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

// Read optical flow data
void PMW3901::read()
{
    // Data that will be readed
    char data[4];
    // Request motion data
    read_reg(PMW3901_MOTION);
    // Read data
    data[0] = read_reg(PMW3901_DELTA_X_L);
    data[1] = read_reg(PMW3901_DELTA_X_H);
    data[2] = read_reg(PMW3901_DELTA_Y_L);
    data[3] = read_reg(PMW3901_DELTA_Y_H);
    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t px_raw = (data[1] << 8 ) | data[0];
    int16_t py_raw = (data[3] << 8 ) | data[2];
    // Convert to SI units [px]
    px = -py_raw * 1.0f;
    py = -px_raw * 1.0f; 
}

// Read data from register
uint8_t PMW3901::read_reg(uint8_t reg)
{
    // Select device by seting chip select low
    cs = 0;
    // Point to register address (set MSB to 0 for read)
    spi.write(reg & 0b01111111);
    // Read data (write a dummy byte 0x00 to receive data from the above register)
    uint8_t data = spi.write(0x00);
    // Deselect the device by seting chip select high
    cs = 1; 
    // Return readed data
    return data;
}

// Write data into register
void PMW3901::write_reg(uint8_t reg, uint8_t data)
{
    // Select the device by seting chip select low
    cs = 0;
    // Point to register address (set MSB to 1 for write)
    spi.write(reg | 0b10000000);
    // Write data into the above register
    spi.write(data);
    // Deselect the device by seting chip select high
    cs = 1; 
}