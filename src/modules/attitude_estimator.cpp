#include "mbed.h"
#include "attitude_estimator.h"

// Class constructor
AttitudeEstimator::AttitudeEstimator() : 
    imu(IMU_SDA,IMU_SCL), 
    led_blue_l(LED_BLUE_L,false)
{
    phi = 0.0f;
    theta = 0.0f;
    psi = 0.0f;
    p = 0.0f;
    q = 0.0f;
    r = 0.0f; 
    p_bias = 0.0f;
    q_bias = 0.0f;
    r_bias = 0.0f; 
}

// Initialize class 
void AttitudeEstimator::init()
{
    // Initialize IMU sensor object
    imu.init();
    // Calibrate gyroscope
    calibrate_gyro();
}

// Calibrates gyroscope by calculating angular velocity bias (rad/s)
void AttitudeEstimator::calibrate_gyro()
{
    // Calculate angular velocities bias (rad/s) by averaging 600 samples during 2 seconds
    for(int i = 0; i<6;i++)
    {
        led_blue_l = !led_blue_l;
        wait(0.5);
    }
    // Calculate angular velocities bias (rad/s) by averaging 600 samples during 2 seconds
    for(int i = 0; i<600;i++)
    {
        imu.read_gyro();
        p_bias += imu.gx/600.0f;
        q_bias += imu.gy/600.0f;
        r_bias += imu.gz/600.0f;
        if ((i%10)==0)
        {
           led_blue_l = !led_blue_l;
        }
        wait(dt);
    }
}

// Estimate Euler angles (rad) and angular velocities (rad/s) from gyroscope data
void AttitudeEstimator::estimate()
{
    // Read gyroscope sensor data
    imu.read();
    // Estimate Euler angles (rad) from accelerometer
    float phi_a = atan2(-imu.ay,-imu.az);
    float theta_a = atan2(imu.ax,-((imu.az>0)-(imu.az<0))*sqrt(pow(imu.ay,2)+pow(imu.az,2)));
    // Estimate angular velocities (rad/s)
    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;
    // Estimate Euler angles (rad) from gyroscope
    float phi_g = phi + (p+q*sin(phi)*tan(theta)+r*cos(phi)*tan(theta))*dt;
    float theta_g = theta + (q*cos(phi)-r*sin(phi))*dt;
    float psi_g = psi + (q*sin(phi)/cos(theta)+r*cos(phi)/cos(theta))*dt;
    // Estimate Euler angles (rad) from accelerometer and gyroscope
    phi = (1.0f-rho_att)*phi_g+rho_att*phi_a;
    theta = (1.0f-rho_att)*theta_g+rho_att*theta_a;
    psi = psi_g;
}