#include "mbed.h"
#include "crazyflie.h"

// Define motor 1 as PWM output object
PwmOut motor_1(MOTOR1);   

// Converts desired angular velocity (rad/s) to PWM signal (%)
float control_motor(float omega)
{
    float pwm = a_2*pow(omega,2)+a_1*omega;
    return pwm;
}

// Main program
int main()
{
    // Turn on motor 1 with 1.000 rad/s for 5s
    motor_1 = control_motor(1000.0);
    wait(5);
    // Turn off motor 1
    motor_1 = 0.0;
    // End of program
    while(1)
    {
    }
}