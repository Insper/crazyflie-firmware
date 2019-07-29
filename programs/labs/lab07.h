#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

// Define serial object
USBSerial serial;

// Define serial command variable
char command;

// Define attitude estimator object
AttitudeEstimator att_est;

// Define Ticker objects
Ticker tic;

// Define Interrupt flag and counter variables
bool flag;

// Define Callback functions
void callback()
{
    flag = true;
}

// Main program
int main()
{
    // Initialize attitude estimator objects
    att_est.init();
    // Initialize interrupt
    tic.attach(&callback, dt);
    while(true) 
    {
        // Estimate attitude
        if (flag) 
        {
            flag = false;
            att_est.estimate();
        }
        // Print attitude
        if (serial.readable()) 
        {
            command = serial.getc();
            if (command == 'p') {
                serial.printf("%f,%f,%f\n",att_est.phi,att_est.theta,att_est.psi);
            }
        }
    }
}