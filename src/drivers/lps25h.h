#ifndef lps25h_h
#define lps25h_h

#include "mbed.h"

// LPS25H I2C address
#define LPS25H_ADDRESS 0b1011101 << 1

// Device identity  
#define WHO_AM_I 0x0F

// Pressure configuration register addresses
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23

// Pressure output register addresses
#define PRESS_OUT_XL 0x28
#define PRESS_OUT_L 0x29
#define PRESS_OUT_H 0x2A

/** LPS25H (barometer sensor) class
 *
 * Example code (print pressure and altitude data on serial port every 0.2 second):
 * @code
 * #include "mbed.h"
 * #include "USBSerial.h"
 * #include "LPS25H.h"
 *
 * USBSerial pc;
 * LPS25H baro(PC_9,PA_8);
 * 
 * int main() 
 * {
 *     baro.init();
 *     while(1)
 *     {
 *          baro.read();
 *          pc.printf("Pressure [hPa]: %6.2f \n", baro.p);
 *          pc.printf("Altitude   [m]: %6.2f \n\n", baro.z);
 *          wait(0.2);
 *     }
 * }
 * @endcode
 * (Need to target to NUCLEO-F401RE board platform)
 */
class LPS25H
{
    public:
        /** Class constructor */
        LPS25H(PinName sda, PinName scl);
        
        /** Initialize sensor */
        bool init();
        /** Read sensor data */
        void read();
        
        /** Pressure data [hPa] */
        float p;
        /** Altitude data [m] */
        float z;
    private:
        /** I2C bus */
        I2C i2c;
        
        /** Setup I2C bus */
        void setup_i2c();
        /** Test I2C bus */
        bool test_i2c();
            
        /** Setup barometer */
        void setup_baro();
        /** Read barometer */
        void read_baro();
        
         /** Write data into register on MPU9250 I2C bus address */
        void write_reg(uint8_t reg, uint8_t data);
        /** Read data from register on MPU9250 I2C bus address */
        char read_reg(uint8_t reg);
};

#endif