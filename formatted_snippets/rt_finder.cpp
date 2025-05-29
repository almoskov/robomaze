/*
    Navigation logic for a pathfinder that tries to navigate
    real time in a maze.

    The used variables, and macros are:
    - sensorValues - array of sensor values from the QTR sensors
    - qtr - QTR object for reading the sensors
    - THRESHOLD - threshold value for detecting the line
    - INTERSECTION_THRESHOLD - minimum number of active sensors to consider it an intersection
    - MAX_SENSORS - maximum number of sensors used
    - collection of functions for motor control:
        - setMotor(int leftSpeed, int rightSpeed) - sets the speed of the motors
        - stopMotors() - stops the motors
        - goForward(int duration) - moves forward for a specified duration
        - turnLeft() - turns left
        - turnRight() - turns right
        - uTurn() - performs a U-turn

*/

bool isIntersection()
{
    int active = 0;
    for (int i = 1; i <= 6; i++)
    {
        if (sensorValues[i] > THRESHOLD)
            active++;
    }
    return active >= INTERSECTION_THRESHOLD;
}

bool isPathLeft() { return sensorValues[1] > THRESHOLD; }
bool isPathCenter() { return sensorValues[3] > THRESHOLD || sensorValues[4] > THRESHOLD; }
bool isPathRight() { return sensorValues[6] > THRESHOLD; }

void handleIntersection()
{
    stopMotors();
    delay(100);
    qtr.read(sensorValues);

    if (isPathRight())
    {
        turnRight();
        goForward(150);
    }
    else if (isPathCenter())
    {
        goForward(200);
    }
    else if (isPathLeft())
    {
        turnLeft();
        goForward(150);
    }
    else
    {
        uTurn();
    }
}

void loop()
{
    qtr.read(sensorValues);

    if (isIntersection())
    {
        handleIntersection();
    }
    else
    {
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