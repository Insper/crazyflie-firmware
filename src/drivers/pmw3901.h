#ifndef pmw3901_h
#define pmw3901_h

#include "mbed.h"

//
#define PMW_ID 0x00
//
#define MOTION 0x02
// Accelerometer output register addresses
#define DELTA_X_L 0x03
#define DELTA_X_H 0x04
#define DELTA_Y_L 0x05
#define DELTA_Y_H 0x06

/** PMW3901 (optical flow sensor) class
 *
 * Example code (print optical flow data on serial port every 0.2 second):
 * @code
 * #include "mbed.h"
 * #include "USBSerial.h"
 * #include "PMW3901.h"
 *
 * USBSerial pc;
 * PMW3901 flow(PA_7,PA_6,PA_5,PB_4);
 * 
 * int main() 
 * {  
 *     flow.init();
 *     while(1)
 *     {
 *          flow.read();
 *          pc.printf("Optical flow [px]: %6.2f %6.2f \n\n", flow.x, flow.y);
 *          wait(0.2);
 *     }
 * }
 * @endcode
 * (Need to target to NUCLEO-F401RE board platform)
 */
class PMW3901
{
    public:
        /** Class constructor */
        PMW3901(PinName mosi, PinName miso, PinName sclk, PinName csel);
        
        /** Initialize optical flow */
        bool init();
        /** **/
        void read();
        
        /** Optical flow data in x-axis (px) **/
        float px;
        /** Optical flow data in y-axis (px) **/
        float py;
    private:
        /** SPI bus */
        SPI spi;
        /** Chip select */
        DigitalOut cs;
        
        /** **/
        void setup_spi();
        /** **/
        bool test_spi();
         /** **/
        void setup_flow();
        /** **/
        void read_flow();
};

#endif