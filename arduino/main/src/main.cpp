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

char motor_command;
char servo_command;
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(50);
    ss.setState(&fs, &bs);
    fs.setState(&ss);
    bs.setState(&ss);
}

void loop() {
    if (stringComplete) {
        motor_command = inputString[0];
        servo_command = inputString[1];
        inputString = "";
        stringComplete = false;
    }

    if (servo_command != ' ') {
        sc.set_goal(servo_command);
        servo_command = ' ';
    }

    if (motor_command != ' ') {
        current_state = current_state->act(motor_command);
        motor_command = ' ';
    }
    sc.reach_goal();
    us_reader.read_sensor();

    if (us_reader.get_distance() < 50 && us_reader.has_lock()) {
        current_state->stop();
        current_state = &ss;
    }

    Serial.print("distance:");
    Serial.print(us_reader.get_distance());
    Serial.print(";servo_state:");
    Serial.print(sc.get_state());
    Serial.print(";motor_state:");
    Serial.print(mc.get_state());
    Serial.print("\r\n");
}

void serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        inputString += inChar;
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}
