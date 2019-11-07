#include "mbed.h"
#include "horizontal_estimator.h"

// Class constructor
HorizontalEstimator::HorizontalEstimator() : flow(PA_7,PA_6,PA_5,PB_4)
{
    x = 0.0;
    y = 0.0;
    u = 0.0;
    v = 0.0;
}

// Initialize class 
void HorizontalEstimator::init()
{
    flow.init();
}

// Predict horizontal velocity from model
void HorizontalEstimator::predict(float phi_r, float theta_r)
{
    x = x+u*dt;
    y = y+v*dt;
    u = u+theta_r*g*dt;
    v = v-phi_r*g*dt;
}

// Correct horizontal velocity with measurements
void HorizontalEstimator::correct(float phi, float theta, float p, float q, float z)
{
    float div = (cos(phi)*cos(theta));
    if (div>0.5)
    {
        flow.read();
        float d = z/div;
        float u_m = (flow.px*sigma+q)*d;
        float v_m = (flow.py*sigma-p)*d;
        u = u+alpha_hor*(u_m-u);
        v = v+alpha_hor*(v_m-v);
    }
}