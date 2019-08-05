#include "mbed.h"
#include "horizontal_estimator.h"

// Class constructor
HorizontalEstimator::HorizontalEstimator() : flow(PA_7,PA_6,PA_5,PB_4)
{
    x = 0.0f;
    y = 0.0f;
    u = 0.0f;
    v = 0.0f;
    x_m_last = 0.0f;
    y_m_last = 0.0f;
}

// Initialize class 
void HorizontalEstimator::init()
{
    flow.init();
}

// Predict horizontal velocity from model
void HorizontalEstimator::predict()
{
    x = x+u*dt;
    y = y+v*dt;
    u = u;
    v = v;
}

// Correct horizontal velocity with measurements
void HorizontalEstimator::correct(float phi, float theta, float p, float q, float z)
{
    float div = (cos(phi)*cos(theta));
    if (div>0.5f)
    {
        flow.read();
        float d = z/div;
        float u_m = (flow.px*sigma+q)*d;
        float v_m = (flow.py*sigma-p)*d;
        float x_m = x_m_last + u_m*dt_flow;
        float y_m = y_m_last + v_m*dt_flow;
        x = (1-alpha_hor)*x+alpha_hor*x_m;
        y = (1-alpha_hor)*y+alpha_hor*y_m;
        u = (1-alpha_hor)*u+alpha_hor*u_m;
        v = (1-alpha_hor)*v+alpha_hor*v_m;
        x_m_last = x_m;
        y_m_last = y_m;
    }
}