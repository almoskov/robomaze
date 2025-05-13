// MazeNavigation.cpp - Implementations for MazeExplorer methods
#include "mazenav.h"

// Replace these stubs with your actual motor control and sensor logic
#include <Arduino.h>
#include <AFMotor.h>
#include <QTRSensors.h>

// === Motor Setup === //
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// === QTR Sensor Setup === //
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

void MazeExplorer::moveForward()
{
    // Simple line following loop to move forward to the next node
    while (!isJunction())
    {
        uint16_t pos = qtr.readLineBlack(sensorValues);
        int error = pos - 2500; // 0 to 5000

        int baseSpeed = 150;
        int correction = error / 20;

        int leftSpeed = baseSpeed - correction;
        int rightSpeed = baseSpeed + correction;

        motor1.setSpeed(leftSpeed);
        motor2.setSpeed(leftSpeed);
        motor3.setSpeed(rightSpeed);
        motor4.setSpeed(rightSpeed);

        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
    }
    stopMotors();
    delay(100); // small pause at junction
}

void MazeExplorer::turnLeft()
{
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(150);
    motor2.setSpeed(150);
    motor3.setSpeed(150);
    motor4.setSpeed(150);
    delay(350); // TODO: adjust for 90 degree turn
    stopMotors();
}

void MazeExplorer::turnRight()
{
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(150);
    motor2.setSpeed(150);
    motor3.setSpeed(150);
    motor4.setSpeed(150);
    delay(350);
    stopMotors();
}

void MazeExplorer::turnAround()
{
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(150);
    motor2.setSpeed(150);
    motor3.setSpeed(150);
    motor4.setSpeed(150);
    delay(700); // TODO adjust for 180 degree turn
    stopMotors();
}

void MazeExplorer::stopMotors()
{
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

bool MazeExplorer::isJunction()
{
    qtr.readCalibrated(sensorValues);
    int activeCount = 0;
    for (int i = 0; i < SensorCount; ++i)
    {
        if (sensorValues[i] > 200)
            activeCount++;
    }
    return activeCount >= 4; // TODO tune threshold for your maze
}
