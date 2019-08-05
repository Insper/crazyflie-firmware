#include "mbed.h"
#include "vertical_estimator.h"

// Class constructor
VerticalEstimator::VerticalEstimator() : range(PB_7,PB_6)
{
    z = 0.0f;
    w = 0.0f;
    z_m_last = 0.0f;
}

// Initialize class 
void VerticalEstimator::init()
{
    range.init();
}

// Predict vertical position and velocity from model
void VerticalEstimator::predict()
{
    z = z+w*dt;
    w = w;
}

// Correct vertical position and velocity with measurement
void VerticalEstimator::correct(float phi, float theta)
{
    range.read();
    if (range.d < 2.0f)
    {
        float z_m = range.d*cos(phi)*cos(theta);
        float w_m = (z_m-z_m_last)/dt_range;
        z = (1-alpha_ver)*z+alpha_ver*z_m;
        w = (1-alpha_ver)*w+alpha_ver*w_m;
        z_m_last = z_m;
    }
}


