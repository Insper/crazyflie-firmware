#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

// Define serial object
USBSerial serial;

// Define IMU sensor object
MPU9250 imu(IMU_SDA,IMU_SCL); // Crazyflie 2.0 IMU sensor
// BMI088 imu(IMU_SDA,IMU_SCL); // Crazyflie 2.1 IMU sensor

// Main program
int main() 
{
    // Initialize IMU sensor object
    imu.init();
    // Print IMU readings every 0.1s
    while(true)
    {
        imu.read();
        serial.printf("Acc [m/s^2]: %6.2f %6.2f %6.2f\n",imu.ax,imu.ay,imu.az);
        serial.printf("Gyr [rad/s]: %6.2f %6.2f %6.2f\n",imu.gx,imu.gy,imu.gz);
        serial.printf("\n");
        wait(0.1);
    }
}
