#ifndef parameters_h
#define parameters_h

#include <cmath>

// Physical constants
const float pi = 3.1416f;
const float g = 9.81f;              // m/s^2

// Quadcopter dimensions
const float m = 30e-3f;             // kg
const float I_xx = 16.0e-6f;        // kg.m^2
const float I_yy = 16.0e-6f;        // kg.m^2
const float I_zz = 29.0e-6f;        // kg.m^2
const float l = 33e-3f;             // m

// Motor constants 
const float a_2 = 1.16e-07f;
const float a_1 = 7.149e-10f;

// Propeller constants
const float kl = 1.726e-08f;        // N.s^2/rad^2
const float kd = 1.426e-10f;        // N.m.s^2/rad^2

// PWM frequencies
const float f_pwm = 500.0f;
const float period_pwm = 1.0f/f_pwm;

// Start-up times
const float motor_test_on_time = 0.05f;
const float motor_test_off_time = 0.15f;

// Interrupt frequencies
const float f = 500.0f;             // Hz
const float f_range = 20.0f;        // Hz 
const float dt = 1.0f/f;            // s
const float dt_range = 1.0f/f_range;// s

// Attitude estimator weighthing (accelerometer X gyroscope)
const float alpha_att = 0.01f;        

// Attitude controller gains (roll/pitch)
const float Ts_phi = 0.3f;//0.4f;         // s
const float OS_phi = 0.005f;//0.010f;       // %
const float zeta_phi = abs(log(OS_phi))/sqrt(pow(log(OS_phi),2)+pow(pi,2));
const float omega_n_phi = 4.0f/(Ts_phi*zeta_phi);
const float kp_phi = pow(omega_n_phi,2.0f);       
const float kd_phi = 2.0f*zeta_phi*omega_n_phi; 
const float kp_theta = kp_phi;       
const float kd_theta = kd_phi; 

// Attitude controller gains (yaw)
const float Ts_psi = 0.6f;          // s
const float OS_psi = 0.005f;        // %
const float zeta_psi = abs(log(OS_psi))/sqrt(pow(log(OS_psi),2)+pow(pi,2));
const float omega_n_psi = 4.0f/(Ts_psi*zeta_psi);
const float kd_psi = pow(omega_n_psi,2.0f);       
const float kp_psi = 2.0f*zeta_psi*omega_n_psi; 

// Vertical estimator weighthing (measurement X prediction)
const float alpha_ver = 0.3f;        

// Vertical controller gains (z)
const float Ts_z = 2.0f;            // s
const float OS_z = 0.005f;          // %
const float zeta_z = abs(log(OS_z))/sqrt(pow(log(OS_z),2)+pow(pi,2));
const float omega_n_z = 4.0f/(Ts_z*zeta_z);
const float kp_z = pow(omega_n_z,2.0f);       
const float kd_z = 2.0f*zeta_z*omega_n_z; 

// Optical flow sensor constant
const float gamma = 42.0f;
const float resolution = 420.0f;
const float sigma = (1.0f/dt)*(2.0f*tan((gamma*pi/180.0f)/2.0f))/resolution; 

// Horizontal estimator weighthing (measurement X prediction)
const float alpha_hor = 0.3f;  

// Horizontal controller gains (x/y)
const float Ts_x = 4.0f;            // s
const float OS_x = 0.005f;          // %
const float zeta_x = abs(log(OS_x))/sqrt(pow(log(OS_x),2)+pow(pi,2));
const float omega_n_x = 4.0f/(Ts_x*zeta_x);
const float kp_x = pow(omega_n_x,2.0f);       
const float kd_x = 2.0f*zeta_x*omega_n_x; 
const float kp_y = kp_x;       
const float kd_y = kd_x; 

#endif