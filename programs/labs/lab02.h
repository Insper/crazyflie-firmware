#include "mbed.h"
#include "crazyflie.h"

// Define motor 1 as PWM output object
PwmOut motor(MOTOR1);   

// Converts desired angular velocity (rad/s) to PWM signal (%)
float control_motor(float omega)
{
    float pwm = alpha*pow(omega,2)+beta*omega;
    return pwm;
}

// Main program
int main()
{
    // Turn on motor 1 with 1.000 rad/s for 0.5s
    motor = control_motor(1000.0);
    wait(0.5);
    // Turn off motor 1
    motor = 0.0;
    // End of program
    while(1)
    {
    }
}