#include <AFMotor.h>
#include <QTRSensors.h>

// QTR sensor setup
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

// Define motors (using Adafruit Motor Shield V1)
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Control variables
int baseSpeed = 150;
float Kp = 0.05; // Proportional gain, adjust as needed

void setup() {
  Serial.begin(9600);

  // Setup QTR sensor array
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, SensorCount);
  qtr.setEmitterPin(2);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Calibrate QTR sensors
  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
    delay(5);
  }

  digitalWrite(LED_BUILTIN, LOW);

  // Print calibration results
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
}

void loop() {
  // Read line position (0 to 5000)
  uint16_t position = qtr.readLineBlack(sensorValues);
  int error = position - 2500; // Center is 2500

  int turn = Kp * error;

  int leftSpeed = constrain(baseSpeed + turn, 0, 255);
  int rightSpeed = constrain(baseSpeed - turn, 0, 255);

  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" | Error: ");
  Serial.print(error);
  Serial.print(" | Left: ");
  Serial.print(leftSpeed);
  Serial.print(" | Right: ");
  Serial.println(rightSpeed);

  driveMotors(leftSpeed, rightSpeed);
}

void driveMotors(int leftSpeed, int rightSpeed) {
  // LEFT side motors (1 and 2)
  motor1.setSpeed(leftSpeed);
  motor1.run(FORWARD);
  motor2.setSpeed(leftSpeed);
  motor2.run(FORWARD);

  // RIGHT side motors (3 and 4)
  motor3.setSpeed(rightSpeed);
  motor3.run(FORWARD);
  motor4.setSpeed(rightSpeed);
  motor4.run(FORWARD);
}
