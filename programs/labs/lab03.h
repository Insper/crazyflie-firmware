#include "mbed.h"
#include "crazyflie.h"

// Define all motors as PWM objects
PwmOut motor_1(MOTOR1);
PwmOut motor_2(MOTOR2);
PwmOut motor_3(MOTOR3);
PwmOut motor_4(MOTOR4);  

// Converts desired angular velocity (rad/s) to PWM signal (%)
float control_motor(float omega)
{
    float pwm = a_2*pow(omega,2)+a_1*omega;
    return pwm;
}

// Main program
int main()
{
    // Turn on all motors with 1.000 rad/s for 5s
    motor_1 = control_motor(1000.0);
    motor_2 = control_motor(1000.0);
    motor_3 = control_motor(1000.0);
    motor_4 = control_motor(1000.0);
    wait(5);
    // Turn off all motors
    motor_1 = 0.0;
    motor_2 = 0.0;
    motor_3 = 0.0;
    motor_4 = 0.0;
    // End of program
    while(1)
    {
    }
}