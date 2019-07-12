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
void AttitudeEstimator::predict()
{
    // Read gyroscope sensor data
    imu.read_gyro();
    // Estimate angular velocities (rad/s)
    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;
    // Estimate Euler angles (rad)
    phi = phi + (p+q*sin(phi)*tan(theta)+r*cos(phi)*tan(theta))*dt;
    theta = theta + (q*cos(phi)-r*sin(phi))*dt;
    psi = psi + (q*sin(phi)/cos(theta)+r*cos(phi)/cos(theta))*dt;
}

// Estimate euler angles (rad) and angular velocity (rad/s)
void AttitudeEstimator::correct()
{  
    // Read accelerometer sensor data
    imu.read_accel();
    // Estimate Euler angles (rad)
    float phi_m = atan2(-imu.ay,-imu.az);
    float theta_m = atan2(imu.ax,-((imu.az>0)-(imu.az<0))*sqrt(pow(imu.ay,2)+pow(imu.az,2)));
    // Ponderate Euler angles (rad) estimation from accelerometer and gyroscope
    phi = (1.0f-rho_att)*phi+rho_att*phi_m;
    theta = (1.0f-rho_att)*theta+rho_att*theta_m;
}