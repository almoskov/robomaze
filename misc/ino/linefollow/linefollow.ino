//Line Follower Robot
 //first , you need to insstall the motor driver for L293D motor driver
// Go to Sketch-> Include Librabry-> Manage Library-> Search for Adafruit Motor Shield V1

/*

    HARDWARE TESTING CODE

*/

#include <AFMotor.h>

#define left A5
#define right A4

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {
  
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  Serial.begin(9600);
  
}

void loop(){

  Serial.println(digitalRead(left));
  
  Serial.println(digitalRead(right));

  
  if(digitalRead(left)==0 && digitalRead(right)==0){
    // Move forward 
    motor1.run(FORWARD);
    motor1.setSpeed(150); // Run Speed from 0 to 255
    motor2.run(FORWARD); 
    motor2.setSpeed(150);// Run Speed from 0 to 255
    motor3.run(FORWARD);
    motor3.setSpeed(150);// Run Speed from 0 to 255
    motor4.run(FORWARD);
    motor4.setSpeed(150);// Run Speed from 0 to 255
  }
  //Compare to sensors
  else if(digitalRead(left)==0 && !analogRead(right)==0){
    //turn right 
    motor1.run(FORWARD);
    motor1.setSpeed(150);
    motor2.run(FORWARD);
    motor2.setSpeed(150);
    motor3.run(BACKWARD);
    motor3.setSpeed(150);
    motor4.run(BACKWARD);
    motor4.setSpeed(150);
    
  }
  //Compare to sensors
  else if(!digitalRead(left)==0 && digitalRead(right)==0){
    //Turn left
    motor1.run(BACKWARD);
    motor1.setSpeed(150);
    motor2.run(BACKWARD);
    motor2.setSpeed(150);
    motor3.run(FORWARD);
    motor3.setSpeed(150);
    motor4.run(FORWARD);
    motor4.setSpeed(150);
   
  }
  //No signals
  else if(!digitalRead(left)==0 && !digitalRead(right)==0){
    //Stop 
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
   
  }
  
}