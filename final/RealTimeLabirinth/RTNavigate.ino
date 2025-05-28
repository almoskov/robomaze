#include <QTRSensors.h>
#include <AFMotor.h>

#define NUM_SENSORS 8
#define TIMEOUT 2500
#define THRESHOLD 700
#define INTERSECTION_THRESHOLD 4

QTRSensorsRC qtr((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 9}, NUM_SENSORS, TIMEOUT, A0);
unsigned int sensorValues[NUM_SENSORS];

AF_DCMotor leftMotor1(1);
AF_DCMotor leftMotor2(2);
AF_DCMotor rightMotor1(3);
AF_DCMotor rightMotor2(4);

const int baseSpeed = 160;
int lastError = 0;

void setMotors(int leftSpeed, int rightSpeed) {
  uint8_t ldir = leftSpeed >= 0 ? FORWARD : BACKWARD;
  uint8_t rdir = rightSpeed >= 0 ? FORWARD : BACKWARD;

  leftMotor1.setSpeed(abs(leftSpeed));
  leftMotor2.setSpeed(abs(leftSpeed));
  leftMotor1.run(ldir);
  leftMotor2.run(ldir);

  rightMotor1.setSpeed(abs(rightSpeed));
  rightMotor2.setSpeed(abs(rightSpeed));
  rightMotor1.run(rdir);
  rightMotor2.run(rdir);
}

void stopMotors() {
  leftMotor1.run(RELEASE);
  leftMotor2.run(RELEASE);
  rightMotor1.run(RELEASE);
  rightMotor2.run(RELEASE);
}

void goForward(int duration = 300) {
  setMotors(baseSpeed, baseSpeed);
  delay(duration);
}

void turnLeft() {
  setMotors(-baseSpeed, baseSpeed);
  delay(350);
}

void turnRight() {
  setMotors(baseSpeed, -baseSpeed);
  delay(350);
}

void uTurn() {
  setMotors(baseSpeed, -baseSpeed);
  delay(600);
}

void followLine() {
  int pos = qtr.readLine(sensorValues);
  int error = pos - 3500;
  int diff = error / 4;
  setMotors(baseSpeed + diff, baseSpeed - diff);
  lastError = error;
}

bool isIntersection() {
  int active = 0;
  for (int i = 1; i <= 6; i++) {
    if (sensorValues[i] > THRESHOLD) active++;
  }
  return active >= INTERSECTION_THRESHOLD;
}

bool isPathLeft()    { return sensorValues[1] > THRESHOLD; }
bool isPathCenter()  { return sensorValues[3] > THRESHOLD || sensorValues[4] > THRESHOLD; }
bool isPathRight()   { return sensorValues[6] > THRESHOLD; }

void handleIntersection() {
  stopMotors();
  delay(100);
  qtr.read(sensorValues);

  if (isPathRight()) {
    turnRight();
    goForward(150);
  }
  else if (isPathCenter()) {
    goForward(200);
  }
  else if (isPathLeft()) {
    turnLeft();
    goForward(150);
  }
  else {
    uTurn();
  }
}

void setup() {
  Serial.begin(9600);

  leftMotor1.setSpeed(0); leftMotor2.setSpeed(0);
  rightMotor1.setSpeed(0); rightMotor2.setSpeed(0);

  for (int i = 0; i < 250; i++) {
    qtr.calibrate();
    delay(20);
  }
}

void loop() {
  qtr.read(sensorValues);

  if (isIntersection()) {
    handleIntersection();
  } else {
    followLine();
  }
  /* This part is optional since the end detection cannot be efficiently done
    // without a specific end marker, which would hinder the performace of either
    // the line following capabilty or the predetermined path finding.
  bool allDark = true;
  for (int i = 1; i <= 6; i++) {
    if (sensorValues[i] > THRESHOLD) {
      allDark = false;
      break;
    }
  }

  if (allDark) {
    stopMotors();
    while (true); // Maze end
  }
  */
}
