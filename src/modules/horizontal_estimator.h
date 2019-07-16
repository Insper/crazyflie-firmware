#ifndef horizontal_estimator_h
#define horizontal_estimator_h

#include "mbed.h"
#include "src/utils/parameters.h"
#include "src/drivers/pmw3901.h"

// Vertical estimator class
class HorizontalEstimator
{
  public:
    // Class constructor
    HorizontalEstimator();
    // Initialize class
    void init();
    // Predict horizontal velocity from model
    void predict();
    // Correct horizontal velocity with measurement
    void correct(float phi, float theta, float p, float q, float z);
    // Horizontal positions (m) and velocities (m/s) estimations
    float x, y, u, v;
  private:
    // Flow sensor object
    PMW3901 flow;
    // Last horizontal position (m) measurements
    float x_m_last, y_m_last;
    
};

#endif
