#include "mbed.h"
#include "crazyflie.h"

// Define red LED (right) as digital output object
DigitalOut led(LED_RED_R,!false);

// Main program
int main()
{
    // Blink LED every second
    while(true) 
    {
        led = !led;
        wait(0.5);
    }
}
