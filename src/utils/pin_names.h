#ifndef pin_names_h
#define pin_names_h

#include "mbed.h"

// Motor pins
const PinName MOTOR1 = PA_1;
const PinName MOTOR2 = PB_11;
const PinName MOTOR3 = PA_15;
const PinName MOTOR4 = PB_9;

// Led pins
const PinName LED_RED_R = PC_3;
const PinName LED_RED_L = PC_0; 
const PinName LED_GREEN_R = PC_2;
const PinName LED_GREEN_L = PC_1;
const PinName LED_BLUE_L = PD_2;

// I2C pins
const PinName IMU_SDA = PC_9; 
const PinName IMU_SCL = PA_8;
const PinName E_SDA = PB_7; 
const PinName E_SCL = PB_6;

// SPI pins
const PinName E_MOSI = PA_7;
const PinName E_MISO = PA_6;
const PinName E_SCK = PA_5;
const PinName E_CS1 = PB_4;

#endif
