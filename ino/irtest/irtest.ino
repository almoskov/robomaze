#define TRESHHOLD 25

const int sensorPin = A5; // Analog pin connected to TCRT5000 OUT
const int sensorPin_2 = A4;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read analog value (0-1023)
  int sensorValue2 = analogRead(sensorPin_2);
  Serial.print("Sensor Value1: ");
  Serial.println(sensorValue);
  if (sensorValue >TRESHHOLD ){
    Serial.println("White");
  }
  else{
    Serial.println("Black");
  }
  Serial.print("Sensor Value2: ");
  Serial.println(sensorValue2);
  if (sensorValue2 > TRESHHOLD ){
    Serial.println("White");
  }
  else{
    Serial.println("Black");
  }
  delay(500); // Delay for readability
}
