#define LEFT_MOTOR_FORWARD  5
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 9
#define RIGHT_MOTOR_BACKWARD 10
#define LIGHT_SENSOR_FLOOR A0

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

bool isPath() {
    return analogRead(LIGHT_SENSOR_FLOOR) < 500; // Assuming black tape gives low value
}

void setup() {
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
    pinMode(LIGHT_SENSOR_FLOOR, INPUT);
    Serial.begin(9600);
}

void loop() {
    Node* start = new Node{0, 0, nullptr};
    push(start);
    visited[0][0] = true;

    while (stackTop >= 0) {
        Node* current = pop();
        if (!current) continue;

        if (isPath()) {
            moveForward();
            push(new Node{current->x, current->y + 1, current});
        } else {
            turnLeft();
            if (!isPath()) {
                turnRight();
                turnRight();
            }
        }
    }
}
