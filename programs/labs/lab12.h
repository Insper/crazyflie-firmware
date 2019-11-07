#include "mbed.h"
#include "crazyflie.h"

// Crazyflie controller objects
Mixer mixer;
AttitudeEstimator att_est;
AttitudeController att_cont;
VerticalEstimator ver_est;
VerticalController ver_cont;
HorizontalEstimator hor_est;
HorizontalController hor_cont;

// Ticker objects
Ticker tic, tic_range;

// Timer objects
Timer tim;

// Time variable
float t = 0.0;

// Interrupt flag and counter variables
bool flag, flag_range;

// Callback functions
void callback()
{
    flag = true;
}
void callback_range()
{
    flag_range = true;
}

// Main program
int main()
{
    // Set references
    float z_r = 0.5f;
    float x_r = 0.0f;
    float y_r = 0.0f;
    float psi_r = 0.0f;
    // Initialize estimators objects
    att_est.init();
    ver_est.init();
    hor_est.init();
    // Initialize interrupts and timers
    tic.attach(&callback, dt);
    tic_range.attach(&callback_range, dt_range);
    tim.start();
    // Arm motors and run controller while stable
    mixer.arm();
    while(abs(att_est.phi) <= pi/4.0f && abs(att_est.theta) <= pi/4.0f &&  abs(att_est.p) <= 4.0f*pi && abs(att_est.q) <= 4.0f*pi && abs(att_est.r) <= 4.0f*pi && t <= 8.0) 
    {
        t = tim.read();
        if (t <= 1.0)
        {
            z_r = t/2.0;
        }
        else if (t >= 5.0)
        {
            z_r = (6.0-t)/2.0;
        }
        else
        {
            z_r = 0.5;
        }
        if (flag) 
        {
            flag = false;
            att_est.estimate();
            ver_est.predict(ver_cont.f_t/(cos(att_est.phi)*cos(att_est.theta)));
            if (flag_range)
            {
                flag_range = false;
                ver_est.correct(att_est.phi,att_est.theta);    
            }
            hor_est.predict(hor_cont.phi_r,hor_cont.theta_r);
            if (ver_est.z >= 0.05f)
            {
                hor_est.correct(att_est.phi,att_est.theta,att_est.p,att_est.q,ver_est.z);
                hor_cont.control(x_r,y_r,hor_est.x,hor_est.y,hor_est.u,hor_est.v);
            }
            ver_cont.control(z_r,ver_est.z,ver_est.w);
            att_cont.control(hor_cont.phi_r,hor_cont.theta_r,psi_r,att_est.phi,att_est.theta,att_est.psi,att_est.p,att_est.q,att_est.r);
            mixer.actuate(ver_cont.f_t/(cos(att_est.phi)*cos(att_est.theta)),att_cont.tau_phi,att_cont.tau_theta,att_cont.tau_psi);
        }
    }
    // Disarm motors and end program
    mixer.disarm();
    while(1);
}