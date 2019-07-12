#ifndef mpu9250_h
#define mpu9250_h
 
#include "mbed.h"
 
// Physical constants
#define GRAVITY 9.80665f
#define PI 3.14159f
 
// MPU9250 I2C bus address
#define MPU9250_ADDRESS 0b1101001 << 1  // Shift 1 bit left because mbed utilizes 8-bit addresses and not 7-bit
 
// Device identity  
#define WHO_AM_I 0x75
 
// Accelerometer configuration registers addresses
#define ACCEL_CONFIG_1 0x1C
#define ACCEL_CONFIG_2 0x1D
// Accelerometer output register addresses
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
 
// Gyroscope configuration registers addresses
#define GYRO_CONFIG 0x1B
// Accelerometer output register addresses
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
 
// Auxiliary I2C configuration registers addresses
#define INT_PIN_CFG 0x37
 
// Accelerometer full-scale ranges
enum accel_scale
{
    ACCEL_SCALE_2G = 0b00, 
    ACCEL_SCALE_4G = 0b01,
    ACCEL_SCALE_8G = 0b10, 
    ACCEL_SCALE_16G = 0b11 
};
 
// Gyroscope full-scale ranges
enum gyro_scale
{
    GYRO_SCALE_250DPS = 0b00,   
    GYRO_SCALE_500DPS = 0b01,  
    GYRO_SCALE_1000DPS = 0b10,  
    GYRO_SCALE_2000DPS = 0b11 
};
 
/** MPU9250 (IMU sensor) class
 *
 * Example code (print accelerometer and gyroscope data on serial port every 0.2 seconds):
 * @code
 * #include "mbed.h"
 * #include "USBSerial.h"
 * #include "MPU9250.h"
 *
 * USBSerial pc;
 * MPU9250 imu(PC_9,PA_8);
 * 
 * int main() 
 * {
 *     imu.init();
 *     while(1)
 *     {
 *          imu.read();
 *          pc.printf("Accel  [m/s^2]: %6.2f %6.2f %6.2f \n", imu.ax, imu.ay, imu.az);
 *          pc.printf("Gyro   [rad/s]: %6.2f %6.2f %6.2f \n\n", imu.gx, imu.gy, imu.gz);
 *          wait(0.2);
 *     }
 * }
 * @endcode
 * (Need to target to NUCLEO-F401RE board platform)
 */
class MPU9250
{
    public:
        /** Class constructor */
        MPU9250(PinName sda, PinName scl);
        
        /** Initialize sensor */
        bool init();
        /** Read accelerometer and gyroscope data */
        void read();
        /** Read accelerometer data */
        void read_accel();
        /** Read gyroscope data */
        void read_gyro();
                
        /** Accelerometer data in x-axis [m/s^2]*/
        float ax;
        /** Accelerometer data in y-axis [m/s^2]*/
        float ay;
        /** Accelerometer data in z-axis [m/s^2]*/
        float az;
        /** Gyroscope data in x-axis [rad/s]*/
        float gx;
        /** Gyroscope data in y-axis [rad/s]*/
        float gy;
        /** Gyroscope data in z-axis [rad/s]*/
        float gz;
    private:
        /** I2C bus */
        I2C i2c;
        
        /** Setup I2C bus */
        void setup_i2c();
        /** Test I2C bus */
        bool test_i2c();
        
        /** Setup auxiliary I2C bus pins */
        void setup_aux_i2c();
        
        /** Setup accelerometer configurations (full-scale range) */
        void setup_accel(accel_scale a_scale = ACCEL_SCALE_16G);
        /** Setup gyroscope  configurations (full-scale range) */
        void setup_gyro(gyro_scale g_scale = GYRO_SCALE_500DPS);
        
        /** Write data into register on MPU9250 I2C bus address */
        void write_reg(uint8_t reg, uint8_t data);
        /** Read data from register on MPU9250 I2C bus address */
        char read_reg(uint8_t reg);
        
        /** Accelerometer resolution [m/s^2 / bit]*/
        float a_res;
        /** Gyroscope resolution [rad/s / bit]*/
        float g_res;
        
};
 
#endif