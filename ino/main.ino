#include "control.h"
#include "pathfinding.h"

void setup() {
    setupMotors();
    setupSensors();
    Serial.begin(9600);
}

void loop() {
    runDFS(); // Call the DFS function from Pathfinding.h
}
