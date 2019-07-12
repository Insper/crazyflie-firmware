#include "mixer.h"

// Class constructor
Mixer::Mixer() : 
    motor_1(MOTOR1), 
    motor_2(MOTOR2), 
    motor_3(MOTOR3), 
    motor_4(MOTOR4), 
    led_red_r(LED_RED_R,true), 
    led_green_r(LED_GREEN_R,true), 
    led_red_l(LED_RED_L,true), 
    led_green_l(LED_GREEN_L,true)
{
    armed = false;
    motor_1.period(period_pwm);
    motor_2.period(period_pwm);
    motor_3.period(period_pwm);
    motor_4.period(period_pwm);
    motor_1 = 0.0f;
    motor_2 = 0.0f;
    motor_3 = 0.0f;
    motor_4 = 0.0f;
}

void Mixer::arm()
{
    if(!armed)
    {
        armed = true;
        led_red_r = false;
        led_red_l = false;
        led_green_r = true;
        led_green_l = true;
        motor_1.period(1.0/440.0);
        motor_1 = 0.2f;
        wait(motor_test_on_time);
        motor_1.period(period_pwm);
        motor_1 = 0.0f;
        wait(motor_test_off_time);
        motor_2.period(1.0/880.0);
        motor_2 = 0.2f;
        wait(motor_test_on_time);
        motor_2.period(period_pwm);
        motor_2 = 0.0f;
        wait(motor_test_off_time);
        motor_3.period(1.0/660.0);
        motor_3 = 0.2f;
        wait(motor_test_on_time);
        motor_3.period(period_pwm);
        motor_3 = 0.0f;
        wait(motor_test_off_time);
        motor_4.period(1.0/550.0);
        motor_4 = 0.2f;
        wait(motor_test_on_time);
        motor_4.period(period_pwm);
        motor_4 = 0.0f;
        wait(motor_test_off_time);
    }
}

void Mixer::disarm()
{
    if(armed)
    {
        armed = false;
        led_red_r = true;
        led_red_l = true;
        led_green_r = false;
        led_green_l = false;
        motor_1 = 0.0f;
        motor_2 = 0.0f;
        motor_3 = 0.0f;
        motor_4 = 0.0f;
    }
}

// Actuate motors with desired total trust force (N) and torques (N.m)
void Mixer::actuate(float f_t, float tau_phi, float tau_theta, float tau_psi)
{
    if(armed)
    {
        force_and_torques_to_angular_velocities(f_t,tau_phi,tau_theta,tau_psi);
        motor_1 = angular_velocity_to_pwm(omega_1);
        motor_2 = angular_velocity_to_pwm(omega_2);
        motor_3 = angular_velocity_to_pwm(omega_3);
        motor_4 = angular_velocity_to_pwm(omega_4);
    }
}

// Converts total trust force (N) and torques (N.m) to angular velocities (rad/s)
void Mixer::force_and_torques_to_angular_velocities(float f_t, float tau_phi, float tau_theta, float tau_psi)
{
    float omega_1_squared = (1.0f/4.0f)*(f_t/kl-tau_phi/(kl*l)-tau_theta/(kl*l)-tau_psi/kd);
    float omega_2_squared = (1.0f/4.0f)*(f_t/kl-tau_phi/(kl*l)+tau_theta/(kl*l)+tau_psi/kd);
    float omega_3_squared = (1.0f/4.0f)*(f_t/kl+tau_phi/(kl*l)+tau_theta/(kl*l)-tau_psi/kd);
    float omega_4_squared = (1.0f/4.0f)*(f_t/kl+tau_phi/(kl*l)-tau_theta/(kl*l)+tau_psi/kd);
    if(omega_1_squared>=0) {
        omega_1 = sqrt(omega_1_squared);
    } else {
        omega_1 = 0.0f;
    }
    if(omega_2_squared>=0) {
        omega_2 = sqrt(omega_2_squared);
    } else {
        omega_2 = 0.0f;
    }
    if(omega_3_squared>=0) {
        omega_3 = sqrt(omega_3_squared);
    } else {
        omega_3 = 0.0f;
    }
    if(omega_4_squared>=0) {
        omega_4 = sqrt(omega_4_squared);
    } else {
        omega_4 = 0.0f;
    }
}

// Converts desired angular velocity (rad/s) to PWM signal (%)
float Mixer::angular_velocity_to_pwm(float omega)
{
    float pwm = alpha*pow(omega,2)+beta*omega;
    return pwm;
}