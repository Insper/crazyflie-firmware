#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

// Define serial object
USBSerial serial;

// Define flow sensor object
PMW3901 flow(E_MOSI,E_MISO,E_SCK,E_CS1);

// Main program
int main()
{
    // Initialize flow sensor object
    flow.init();
    // Print flow readings every 0.1s
    while(true) 
    {
        flow.read();
        serial.printf("Flow [px]: %6.0f %6.0f \n",flow.px,flow.py);
        wait(0.1);
    }
}
