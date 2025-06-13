#ifndef CONTROL_H
#define CONTROL_H

#define LEFT_MOTOR_FORWARD 5
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 9
#define RIGHT_MOTOR_BACKWARD 10
#define LIGHT_SENSOR_FLOOR A0

void setupMotors()
{
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}

void setupSensors()
{
    pinMode(LIGHT_SENSOR_FLOOR, INPUT);
}

void moveForward()
{
    analogWrite(LEFT_MOTOR_FORWARD, 255);
    analogWrite(RIGHT_MOTOR_FORWARD, 255);
    delay(500);
}

void turnLeft()
{
    analogWrite(LEFT_MOTOR_FORWARD, 0);
    analogWrite(RIGHT_MOTOR_FORWARD, 255);
    delay(300);
}

void turnRight()
{
    analogWrite(LEFT_MOTOR_FORWARD, 255);
    analogWrite(RIGHT_MOTOR_FORWARD, 0);
    delay(300);
}

bool isPath()
{
    return analogRead(LIGHT_SENSOR_FLOOR) < 500; // Assuming black tape gives low value
}

#endif
