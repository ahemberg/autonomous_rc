#include <Arduino.h>
#include <UltraSoundReader.h>
#include <MotorController.h>
#include <ServoController.h>

// Defines for UltraSoundReader
#define TRIG 11
#define ECHO  12

// Defines for ServoController
#define ENABLE_SERVO 8
#define PWM_SERVO 9
#define SERVO_AIN1 10
#define SERVO_AIN2 3
#define SERVO_MEAS A0

// Defines for MotorController
#define INPUT1_MOTOR 5
#define INPUT2_MOTOR 6
#define ENABLE_MOTOR 4

short int speed = 0, angle = 0, old_angle = 100;
bool stopped = false;

MotorController mc = MotorController(INPUT1_MOTOR, INPUT2_MOTOR, ENABLE_MOTOR);
ServoController sc = ServoController(
    PWM_SERVO, ENABLE_SERVO, SERVO_AIN1, SERVO_AIN2, 80, SERVO_MEAS
);
UltraSoundReader us_reader = UltraSoundReader(TRIG, ECHO);

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(50);
}

void loop() {
    us_reader.read_sensor();

    if (us_reader.get_distance() < 50 && us_reader.has_lock()) {
        speed = 0;
    }

    if (speed ==  -100) {
        mc.backward(200);
        stopped = false;
    } else if (speed == 100) {
        mc.forward(200);
        stopped = false;
    } else if (!stopped) {
        mc.break_engine();
        delay(100);
        mc.disable_engine();
        stopped = true;
    }

    if (angle >= -100 && angle <= 100 && angle != old_angle) {
        sc.set_goal(angle);
        old_angle = angle;
    }
    sc.reach_goal();
}

void serialEvent() {
    char command;

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
            default:
              angle = 0;
              speed = 0;
              break;
        }
        Serial.print(command);
        Serial.print(':');
        Serial.print(angle);
        Serial.print(':');
        Serial.print(speed);
        Serial.println();
    }

}
