#include <Arduino.h>
#include <UltraSoundReader.h>
#include <MotorController.h>
#include <ServoController.h>
#include <pin_definitions.h>
#include <SerialCommunication.h>

#define BUFFER_SIZE 10   // maximum number of bytes to read from serial port


byte buffer[BUFFER_SIZE];
int bytesRead;
short int angle = 0, old_angle = 100;
bool stopped = false;

MotorController mc = MotorController(INPUT1_MOTOR, INPUT2_MOTOR, ENABLE_MOTOR);
ServoController sc = ServoController(
    PWM_SERVO, ENABLE_SERVO, SERVO_AIN1, SERVO_AIN2, 80, SERVO_MEAS
);
UltraSoundReader us_reader = UltraSoundReader(TRIG, ECHO);
SerialCommunication scom = SerialCommunication(&mc, &sc, &us_reader);


void setup() {
    Serial.begin(9600);
    Serial.setTimeout(50);
}

void loop() {
    us_reader.read_sensor();

    if (us_reader.get_distance() < 50 && us_reader.has_lock()) {
        mc.set_speed(0);
    }

    // TODO: move this to scom.processPackage()
    if (angle >= -100 && angle <= 100 && angle != old_angle) {
        sc.set_goal(angle);
        old_angle = angle;
    }
    sc.reach_goal();
}

void serialEvent() {
    bytesRead = scom.readBuffer(buffer, BUFFER_SIZE);  // read serial port into buffer

    byte receivedPackage[bytesRead];  // initiate package byte array
    memcpy(receivedPackage, buffer, bytesRead);  // copy data from buffer to package

    if (scom.validatePackage(receivedPackage, bytesRead)==0){
        scom.processPackage(receivedPackage);
    }
}
