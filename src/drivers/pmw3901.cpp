#include "pmw3901.h"

/** Class constructor */
PMW3901::PMW3901(PinName mosi, PinName miso, PinName sclk, PinName csel) : spi(mosi, miso, sclk), cs(csel)
{
}
    
/** Initialize optical flow */
bool PMW3901::init()
{
    setup_spi();
    if (test_spi())
    {
        setup_flow();
        return true;
    }
    else
    {
        return false;
    }
}

void PMW3901::read()
{
    read_flow();
}

void PMW3901::setup_spi()
{
    // Deselect the device by seting chip select high
    cs = 1;
 
    // Setup the spi format for 8 bit data and mode 3 (high steady state clock and second edge capture)
    spi.format(8,3);
    // Setup the spi frequency to 2MHz
    spi.frequency(2000000);
}

bool PMW3901::test_spi()
{
    // 
    char id;
     
    // Select the device by seting chip select low
    cs = 0;
    // Write the register to read sensor ID (set MSB to 0 for read)
    spi.write(PMW_ID & 0b01111111); 
    // Write a dummy byte 0x00 to receive the chip ID
    id = spi.write(0x00);
    // Deselect the device by seting chip select high
    cs = 1; 
    
    //
    if (id == 0x49)
    {
        return true;
    }
    else
    {
        return false;
    }   
}

void PMW3901::setup_flow()
{
    // Select the device by seting chip select low
    cs = 0;
    
    //
    spi.write(0x3A | 0b10000000); spi.write(0x5A);
    
    // 
    spi.write(0x02 & 0b01111111); spi.write(0x00);
    // 
    spi.write(0x03 & 0b01111111); spi.write(0x00);
    spi.write(0x04 & 0b01111111); spi.write(0x00);
    spi.write(0x05 & 0b01111111); spi.write(0x00);
    spi.write(0x06 & 0b01111111); spi.write(0x00);
    
    //
    spi.write(0x7F | 0b10000000); spi.write(0x00);
    spi.write(0x61 | 0b10000000); spi.write(0xAD);
    spi.write(0x7F | 0b10000000); spi.write(0x03);
    spi.write(0x40 | 0b10000000); spi.write(0x00);
    spi.write(0x7F | 0b10000000); spi.write(0x05);
    spi.write(0x41 | 0b10000000); spi.write(0xB3);
    spi.write(0x43 | 0b10000000); spi.write(0xF1);
    spi.write(0x45 | 0b10000000); spi.write(0x14);
    spi.write(0x5B | 0b10000000); spi.write(0x32);
    spi.write(0x5F | 0b10000000); spi.write(0x34);
    spi.write(0x7B | 0b10000000); spi.write(0x08);
    spi.write(0x7F | 0b10000000); spi.write(0x06);
    spi.write(0x44 | 0b10000000); spi.write(0x1B);
    spi.write(0x40 | 0b10000000); spi.write(0xBF);
    spi.write(0x4E | 0b10000000); spi.write(0x3F);
    spi.write(0x7F | 0b10000000); spi.write(0x08);
    spi.write(0x65 | 0b10000000); spi.write(0x20);
    spi.write(0x6A | 0b10000000); spi.write(0x18);
    spi.write(0x7F | 0b10000000); spi.write(0x09);
    spi.write(0x4F | 0b10000000); spi.write(0xAF);
    spi.write(0x5F | 0b10000000); spi.write(0x40);
    spi.write(0x48 | 0b10000000); spi.write(0x80);
    spi.write(0x49 | 0b10000000); spi.write(0x80);
    spi.write(0x57 | 0b10000000); spi.write(0x77);
    spi.write(0x60 | 0b10000000); spi.write(0x78);
    spi.write(0x61 | 0b10000000); spi.write(0x78);
    spi.write(0x62 | 0b10000000); spi.write(0x08);
    spi.write(0x63 | 0b10000000); spi.write(0x50);
    spi.write(0x7F | 0b10000000); spi.write(0x0A);
    spi.write(0x45 | 0b10000000); spi.write(0x60);
    spi.write(0x7F | 0b10000000); spi.write(0x00);
    spi.write(0x4D | 0b10000000); spi.write(0x11);
    spi.write(0x55 | 0b10000000); spi.write(0x80);
    spi.write(0x74 | 0b10000000); spi.write(0x1F);
    spi.write(0x75 | 0b10000000); spi.write(0x1F);
    spi.write(0x4A | 0b10000000); spi.write(0x78);
    spi.write(0x4B | 0b10000000); spi.write(0x78);
    spi.write(0x44 | 0b10000000); spi.write(0x08);
    spi.write(0x45 | 0b10000000); spi.write(0x50);
    spi.write(0x64 | 0b10000000); spi.write(0xFF);
    spi.write(0x65 | 0b10000000); spi.write(0x1F);
    spi.write(0x7F | 0b10000000); spi.write(0x14);
    spi.write(0x65 | 0b10000000); spi.write(0x60);
    spi.write(0x66 | 0b10000000); spi.write(0x08);
    spi.write(0x63 | 0b10000000); spi.write(0x78);
    spi.write(0x7F | 0b10000000); spi.write(0x15);
    spi.write(0x48 | 0b10000000); spi.write(0x58);
    spi.write(0x7F | 0b10000000); spi.write(0x07);
    spi.write(0x41 | 0b10000000); spi.write(0x0D);
    spi.write(0x43 | 0b10000000); spi.write(0x14);
    spi.write(0x4B | 0b10000000); spi.write(0x0E);
    spi.write(0x45 | 0b10000000); spi.write(0x0F);
    spi.write(0x44 | 0b10000000); spi.write(0x42);
    spi.write(0x4C | 0b10000000); spi.write(0x80);
    spi.write(0x7F | 0b10000000); spi.write(0x10);
    spi.write(0x5B | 0b10000000); spi.write(0x02);
    spi.write(0x7F | 0b10000000); spi.write(0x07);
    spi.write(0x40 | 0b10000000); spi.write(0x41);
    spi.write(0x70 | 0b10000000); spi.write(0x00);
    
    //
    wait(0.1);
    spi.write(0x32 | 0b10000000); spi.write(0x44);
    spi.write(0x7F | 0b10000000); spi.write(0x07);
    spi.write(0x40 | 0b10000000); spi.write(0x40);
    spi.write(0x7F | 0b10000000); spi.write(0x06);
    spi.write(0x62 | 0b10000000); spi.write(0xf0);
    spi.write(0x63 | 0b10000000); spi.write(0x00);
    spi.write(0x7F | 0b10000000); spi.write(0x0D);
    spi.write(0x48 | 0b10000000); spi.write(0xC0);
    spi.write(0x6F | 0b10000000); spi.write(0xd5);
    spi.write(0x7F | 0b10000000); spi.write(0x00);
    spi.write(0x5B | 0b10000000); spi.write(0xa0);
    spi.write(0x4E | 0b10000000); spi.write(0xA8);
    spi.write(0x5A | 0b10000000); spi.write(0x50);
    spi.write(0x40 | 0b10000000); spi.write(0x80);
    
    // Deselect the device by seting chip select high
    cs = 1;
}

void PMW3901::read_flow()
{
    // Data that we're going to read
    char data[4];
    
    // Select the device by seting chip select low
    cs = 0; 
        
    //   
    spi.write(MOTION & 0b01111111); spi.write(0x00); 
    // Write the register to read sensor ID (set MSB to 0 for read) 
    spi.write(DELTA_X_L & 0b01111111); data[0] = spi.write(0x00); 
    spi.write(DELTA_X_H & 0b01111111); data[1] = spi.write(0x00); 
    spi.write(DELTA_Y_L & 0b01111111); data[2] = spi.write(0x00); 
    spi.write(DELTA_Y_H & 0b01111111); data[3] = spi.write(0x00); 

    // Reassemble the data (two 8 bit data into one 16 bit data)
    int16_t px_raw = (data[1] << 8 ) | data[0];
    int16_t py_raw = (data[3] << 8 ) | data[2];
    // Convert to SI units [px]
    px = -py_raw * 1.0f;
    py = -px_raw * 1.0f; 
    
    // Deselect the device by seting chip select high
    cs = 1;   
}
        