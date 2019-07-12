#include "mbed.h"
#include "vertical_controller.h"

// Class constructor
VerticalController::VerticalController()
{
    f_t = 0.0f;
}

// Control thrust force (N) given vertical position (m) and velocity (m/s)
void VerticalController::control(float z_r, float z, float w)
{
    f_t = m*(g+control_state_regulator(z_r,z,w,kp_z,kd_z));
}

// Control aceleration given reference position (m) and current position (m) and velocity (m/s) with given controller gains
float VerticalController::control_state_regulator(float pos_r, float pos, float vel, float kp, float kd)
{
    float acc_r = kp*(pos_r-pos) + kd*(0.0f-vel); 
    return acc_r;
}