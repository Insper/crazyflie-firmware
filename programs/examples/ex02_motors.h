#include "mbed.h"
#include "crazyflie.h"

// Define motor 1 as PWM output object
PwmOut motor(MOTOR1);

// Main program
int main()
{
    // Turn motor on (20% power) and off every second
    while(true) 
    {
        motor = 0.2;
        wait(0.5);
        motor = 0.0;
        wait(0.5);
    }
}