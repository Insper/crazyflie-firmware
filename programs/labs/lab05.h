#include "mbed.h"
#include "crazyflie.h"

// Define all motors as PWM objects
PwmOut motor_1(MOTOR1);
PwmOut motor_2(MOTOR2);
PwmOut motor_3(MOTOR3);
PwmOut motor_4(MOTOR4);  

// Define angular velocities (rad/s)
float omega_1;
float omega_2;
float omega_3;
float omega_4;

// Converts desired angular velocity (rad/s) to PWM signal (%)
float control_motor(float omega)
{
    float pwm = alpha*pow(omega,2)+beta*omega;
    return pwm;
}

// Converts total trust force (N) and torques (N.m) to angular velocities (rad/s)
void mixer(float f_t, float tau_phi, float tau_theta, float tau_psi)
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

// Actuate motors with desired total trust force (N) and torques (N.m)
void actuate(float f_t, float tau_phi, float tau_theta, float tau_psi)
{
    mixer(f_t,tau_phi,tau_theta,tau_psi);
    motor_1 = control_motor(omega_1);
    motor_2 = control_motor(omega_2);
    motor_3 = control_motor(omega_3);
    motor_4 = control_motor(omega_4);
}

// Main program
int main()
{
    // Actuate motor with 70% mg total thrust force (N) and zero torques
    actuate(0.7*m*g,0,0,0);
    wait(5);
    // Turn off all motors
    actuate(0,0,0,0);
    // End of program
    while(1)
    {
    }
}