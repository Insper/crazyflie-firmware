#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

// Define serial object
USBSerial serial;

// Define range sensor object
VL53L0X range(E_SDA,E_SCL); // FLow deck range sensor
// VL53L1X range(E_SDA,E_SCL); // Flow deck v2 range sensor

// Main program
int main()
{
    // Initialize range sensor object
    range.init();
    // Print range readings every 0.1s
    while(true) 
    {
        range.read();
        serial.printf("Range [m]: %6.2f \n",range.d);
        wait(0.1);
    }
}
