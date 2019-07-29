#ifndef attitude_estimator_h
#define attitude_estimator_h

#include "mbed.h"
#include "src/utils/pin_names.h"
#include "src/utils/parameters.h"
#include "src/drivers/mpu9250.h"

// Attitude estimator class
class AttitudeEstimator
{
  public:
    // Class constructor
    AttitudeEstimator();
    // Initialize class
    void init();
    // Estimate Euler angles (rad) and angular velocities (rad/s)
    void estimate();
    // Euler angles (rad)
    float phi, theta, psi;
    // Angular velocities (rad/s)
    float p, q, r;
  private:
    // IMU sensor object
    MPU9250 imu;
    // LED digital output
    DigitalOut led_blue_l;
    // Calibrates gyroscope by calculating angular velocity bias (rad/s)
    void calibrate_gyro();
    // Angular velocities bias (rad/s)
    float p_bias, q_bias, r_bias; 
};

#endif