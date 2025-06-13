#include <AFMotor.h>
#include "PDPathFinder.h"
#include <QTRSensors.h>

#define NUM_SENSORS 8
#define TIMEOUT 2500
#define THRESHOLD 700
#define INTERSECTION_THRESHOLD 4

// this constant may be used for the speed of the motors
// the value is subject to change based on the power to weight ration of the robot
// and other physical enviromental factors
// #define SPEED_VALUE 160

QTRSensorsRC qtr((unsigned char[]){2, 3, 4, 5, 6, 7, 8, 9}, NUM_SENSORS, TIMEOUT, A0);
PathFinder pf;

short *directions;
int directionIndex = 0;

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

bool isIntersection(unsigned int *sensorValues)
{
  int count = 0;
  for (int i = 1; i <= 6; i++)
  {
    if (sensorValues[i] > THRESHOLD)
      count++;
  }
  return count >= INTERSECTION_THRESHOLD;
}

void followLine()
{
  unsigned int sensorValues[NUM_SENSORS];
  int position = qtr.readLine(sensorValues);
  int error = position - 3500;

  int motorSpeed = error / 4;
  setMotor(baseSpeed + motorSpeed, baseSpeed - motorSpeed);
}

void setup()
{
  Serial.begin(9600);
  directions = pf.solve();

  // Calibrate QTR sensors
  for (int i = 0; i < 250; i++)
  {
    qtr.calibrate();
    delay(20);
  }
}

void loop()
{
  unsigned int sensorValues[NUM_SENSORS];
  qtr.read(sensorValues);

  if (directionIndex < pf.moveCount)
  {
    if (isIntersection(sensorValues))
    {
      short dir = directions[directionIndex++];
      delay(200); // Debounce
      if (dir == 1)
      {
        goForward();
      }
      else if (dir == 2)
      {
        turnLeft();
      }
      else if (dir == 3)
      {
        turnRight();
      }
    }
    else
    {
      followLine();
    }
  }
  else
  {
    // End of path, check if line disappears
    bool allDark = true;
    for (int i = 1; i <= 6; i++)
    {
      if (sensorValues[i] > THRESHOLD)
      {
        allDark = false;
        break;
      }
    }
    if (allDark)
    {
      stopMotors();
      while (true)
        ; // Halt
    }
    else
    {
      followLine();
    }
  }
}
