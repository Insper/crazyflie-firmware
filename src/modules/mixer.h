#ifndef mixer_h
#define mixer_h

#include "mbed.h"
#include "src/utils/pin_names.h"
#include "src/utils/parameters.h"

// Mixer class
class Mixer
{
  public:
    // Class constructor
    Mixer();
    //
    void arm();
    //
    void disarm();
    // Actuate motors with desired total trust force (N) and torques (N.m)
    void actuate(float f_t, float tau_phi, float tau_theta, float tau_psi);
  private:
    // Motors PWM outputs
    PwmOut motor_1, motor_2, motor_3, motor_4;
    // LED digital outputs
    DigitalOut led_red_r, led_green_r, led_red_l, led_green_l;
    //
    bool armed;
    // Angular velocities (rad/s)
    float omega_1, omega_2, omega_3, omega_4;
    // Converts total trust force (N) and torques (N.m) to angular velocities (rad/s)
    void force_and_torques_to_angular_velocities(float f_t, float tau_phi, float tau_theta, float tau_psi);
    // Converts desired angular velocity (rad/s) to PWM signal (%)
    float angular_velocity_to_pwm(float omega);
};

#endif