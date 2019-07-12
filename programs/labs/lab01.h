#include "mbed.h"
#include "crazyflie.h"

// Define all LEDs as digital output objects
DigitalOut led_red_r(LED_RED_R,!false);
DigitalOut led_red_l(LED_RED_L,!false);
DigitalOut led_green_r(LED_GREEN_R,!false); 
DigitalOut led_green_l(LED_GREEN_L,!false);
DigitalOut led_blue_l(LED_BLUE_L,false);

// Define all motors as PWM objects
PwmOut motor_1(MOTOR1);
PwmOut motor_2(MOTOR2);
PwmOut motor_3(MOTOR3);
PwmOut motor_4(MOTOR4);

// Main program
int main()
{
    // Blink blue LED indicating inicialization (5 seconds)
    for(int i=1; i<=50; i++) 
    {
        led_blue_l = !led_blue_l;
        wait(0.1);
    }
    // Turn on red LEDs indicating motors are armed
    led_red_r = !true;
    led_red_l = !true;
    // Test all motors with different frequencies (to make different noises)
    for(int i = 1; i<= 3; i++) 
    {
        // Motor 1
        motor_1.period(1.0/440.0);
        motor_1 = 0.2;
        wait(0.05);
        motor_1 = 0.0;
        wait(0.15);
        // Motor 2
        motor_2.period(1.0/880.0);
        motor_2 = 0.2;
        wait(0.05);
        motor_2 = 0.0;
        wait(0.15);
        // Motor 3
        motor_3.period(1.0/660.0);
        motor_3 = 0.2;
        wait(0.05);
        motor_3 = 0.0;
        wait(0.15);
        // Motor 4
        motor_4.period(1.0/550.0);
        motor_4 = 0.2;
        wait(0.05);
        motor_4 = 0.0;
        wait(0.15);
    }
    // Turn off red LEDs indicating motors are disarmed
    led_red_r = !false;
    led_red_l = !false;
    // Blink green LEDs indicating end of program
    while(1)
    {
        led_green_r = !led_green_r;
        led_green_l = !led_green_l;
        wait(0.1);
    }
}