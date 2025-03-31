/* This is only a demo application which uses
* simple graph traversal to solve an easy maze
* and control a robot equipped with a light sensor
* to be able to navigate following a line made by black tape.
*/

#define LEFT_MOTOR_FORWARD  5
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 9
#define RIGHT_MOTOR_BACKWARD 10
#define LIGHT_SENSOR_LEFT A0
#define LIGHT_SENSOR_RIGHT A1
#define LIGHT_SENSOR_FRONT A2

struct Node {
    int x, y;
    Node* parent;
};

const int mazeSize = 10;
bool visited[mazeSize][mazeSize] = {false};
Node* stack[mazeSize * mazeSize];
int stackTop = -1;

void push(Node* node) {
    stack[++stackTop] = node;
}

Node* pop() {
    return stackTop >= 0 ? stack[stackTop--] : nullptr;
}

void moveForward() {
    analogWrite(LEFT_MOTOR_FORWARD, 255);
    analogWrite(RIGHT_MOTOR_FORWARD, 255);
    delay(500);
}

void turnLeft() {
    analogWrite(LEFT_MOTOR_FORWARD, 0);
    analogWrite(RIGHT_MOTOR_FORWARD, 255);
    delay(300);
}

void turnRight() {
    analogWrite(LEFT_MOTOR_FORWARD, 255);
    analogWrite(RIGHT_MOTOR_FORWARD, 0);
    delay(300);
}

bool isPath(int sensor) {
    return analogRead(sensor) > 500;
}

void setup() {
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
    pinMode(LIGHT_SENSOR_LEFT, INPUT);
    pinMode(LIGHT_SENSOR_RIGHT, INPUT);
    pinMode(LIGHT_SENSOR_FRONT, INPUT);
    Serial.begin(9600);
}

void loop() {
    Node* start = new Node{0, 0, nullptr};
    push(start);
    visited[0][0] = true;

    while (stackTop >= 0) {
        Node* current = pop();
        if (!current) continue;

        if (isPath(LIGHT_SENSOR_FRONT)) {
            moveForward();
            push(new Node{current->x, current->y + 1, current});
        } else if (isPath(LIGHT_SENSOR_LEFT)) {
            turnLeft();
            moveForward();
            push(new Node{current->x - 1, current->y, current});
        } else if (isPath(LIGHT_SENSOR_RIGHT)) {
            turnRight();
            moveForward();
            push(new Node{current->x + 1, current->y, current});
        }
    }
}

