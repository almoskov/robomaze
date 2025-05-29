/*
 *   Driver logic for controlling the motors
 *   using the Adafruit Motor Shield v1.
 *   The values of the setMotor parameters
 *   may change, since the performance of the motors
 *   depends on the power supply and the load.
 */
#include <AFMotor.h>

// Motors on Adafruit Motor Shield v1
AF_DCMotor leftMotor1(1);  // M1
AF_DCMotor leftMotor2(2);  // M2
AF_DCMotor rightMotor1(3); // M3
AF_DCMotor rightMotor2(4); // M4

// Motor speed base
const int baseSpeed = 160;
int lastError = 0;

void setMotor(int leftSpeed, int rightSpeed)
{
    // Set left motors
    uint8_t ldir = leftSpeed >= 0 ? FORWARD : BACKWARD;
    leftMotor1.setSpeed(abs(leftSpeed));
    leftMotor2.setSpeed(abs(leftSpeed));
    leftMotor1.run(ldir);
    leftMotor2.run(ldir);

    // Set right motors
    uint8_t rdir = rightSpeed >= 0 ? FORWARD : BACKWARD;
    rightMotor1.setSpeed(abs(rightSpeed));
    rightMotor2.setSpeed(abs(rightSpeed));
    rightMotor1.run(rdir);
    rightMotor2.run(rdir);
}

void stopMotors()
{
    leftMotor1.run(RELEASE);
    leftMotor2.run(RELEASE);
    rightMotor1.run(RELEASE);
    rightMotor2.run(RELEASE);
}

void goForward()
{
    setMotor(160, 160);
    delay(300);
}

void turnLeft()
{
    setMotor(-160, 160);
    delay(350);
}

void turnRight()
{
    setMotor(160, -160);
    delay(350);
}