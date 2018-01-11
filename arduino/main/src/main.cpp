#define TRIG 11
#define ECHO  12

#include <Arduino.h>

#include <UltraSoundReader.h>
#include <StopState.h>
#include <ForwardState.h>
#include <BackwardState.h>
#include <EngineState.h>
#include <MotorController.h>
#include <ServoController.h>

MotorController mc = MotorController();

StopState ss = StopState(mc);
ForwardState fs = ForwardState(mc);
BackwardState bs = BackwardState(mc);
ServoController sc = ServoController(mc);
EngineState *current_state = &ss;

UltraSoundReader us_reader = UltraSoundReader(TRIG,ECHO);

short int currentSpeed = 0;
short int currentAngle = 0;

void setDirection(int speed, int angle){
    // speed = motor speed in % of max, [-100, 100]. 0=stop
    // angle = turn angle in % of max, [-100, 100]
    if ((speed != currentSpeed) && (speed < 101)) {
        current_state = current_state->act(speed);
        currentSpeed = speed;
    }
    if ((angle != currentAngle) && (angle < 101)) {
        sc.set_goal(angle);
        sc.reach_goal();
        currentAngle = angle;
    }
}


void setup() {
    Serial.begin(9600);
    Serial.setTimeout(50);
    ss.setState(&fs, &bs);
    fs.setState(&ss);
    bs.setState(&ss);
}

void loop() {
    us_reader.read_sensor();

    if (us_reader.get_distance() < 50 && us_reader.has_lock()) {
        current_state->stop();
        current_state = &ss;
    }
}

void serialEvent() {
    char command;
    short int speed=999, angle=999; // function setDirection() ignores values>100

    while (Serial.available()) {
        command = (char)Serial.read();

        switch (command) {
            case 'a':
              angle = -100;
              break;
            case 'd':
              angle = 100;
              break;
            case 'x':
              angle = 0;
              break;
            case 'w':
              speed = 100;
              break;
            case 's':
              speed = -100;
              break;
            case 'q':
              speed = 0;
              break;
        }

        setDirection(speed, angle);
    }

}
