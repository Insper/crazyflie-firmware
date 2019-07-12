#ifndef vertical_controller_h
#define vertical_controller_h

#include "mbed.h"
#include "parameters.h"

// Vertical controller class
class VerticalController
{
  public:
    // Class constructor
    VerticalController();
    // Control total thrust force (N) given reference vertical position (m) and current vertical position (m) and velocity (m/s)
    void control(float z_r, float z, float w);
    // Total thrust force (N)
    float f_t;
  private:
    // Control aceleration given reference position (m) and current position (m) and velocity (m/s) with given controller gains
    float control_state_regulator(float position_r, float position, float velocity, float kp, float kd);  
};

#endif