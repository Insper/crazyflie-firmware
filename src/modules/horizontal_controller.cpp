#include "mbed.h"
#include "horizontal_controller.h"

// Class constructor
HorizontalController::HorizontalController()
{
    phi_r = 0.0f;
    theta_r = 0.0f;
}

// Control reference roll and pitch angles (rad) given reference positions (m) and current positions (m) and velocities (m/s)
void HorizontalController::control(float x_r, float y_r, float x, float y, float u, float v)
{
    phi_r = -control_state_regulator(y_r,y,v,kp_y,kd_y)/g;
    theta_r = control_state_regulator(x_r,x,u,kp_x,kd_x)/g;
}

// Control acceleration given reference position (m) and current position (m) and velocity (m/s) with given controller gains
float HorizontalController::control_state_regulator(float pos_r, float pos, float vel, float kp, float kd)
{
    float acc_r = kp*(pos_r-pos) + kd*(0.0f-vel); 
    return acc_r;
}