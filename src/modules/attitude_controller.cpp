#include "mbed.h"
#include "attitude_controller.h"

// Class constructor
AttitudeController::AttitudeController()
{
    tau_phi = 0.0f;
    tau_theta = 0.0f;
    tau_psi = 0.0f;
}

// Control torques (N.m) given reference angles (rad) and current angles (rad) and angular velocities (rad/s)
void AttitudeController::control(float phi_r, float theta_r, float psi_r, float phi, float theta, float psi, float p, float q, float r)
{
    tau_phi = control_state_regulator(phi_r, phi, p, kp_phi, kd_phi, I_xx);
    tau_theta = control_state_regulator(theta_r, theta, q, kp_theta, kd_theta, I_yy);
    tau_psi = control_state_regulator(psi_r, psi, r, kp_psi, kd_psi, I_zz);
}

// Control torque (N.m) given reference angle (rad) and current angle (rad) and angular velocity (rad/s) with given time constants (s) and moment of inertia (kg.m^2)
float AttitudeController::control_state_regulator(float angle_r, float angle, float rate, float kp, float kd, float I)
{
    float acc_r =  I*(kp*(angle_r-angle)+kd*(0.0f-rate));
    return acc_r;
}