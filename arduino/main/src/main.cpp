#include <Arduino.h>
#include <UltraSoundReader.h>
#include <MotorController.h>
#include <ServoController.h>
#include <pin_definitions.h>
#include <SerialCommunication.h>

#define BUFFER_SIZE 10   // maximum number of bytes to read from serial port


byte buffer[BUFFER_SIZE];
int bytesRead;
bool stopped = false;

MotorController mc = MotorController(INPUT1_MOTOR, INPUT2_MOTOR, ENABLE_MOTOR);
ServoController sc = ServoController(
    PWM_SERVO, ENABLE_SERVO, SERVO_AIN1, SERVO_AIN2, 200, SERVO_MEAS
);
UltraSoundReader us_reader = UltraSoundReader(TRIG, ECHO);
SerialCommunication scom = SerialCommunication(&mc, &sc, &us_reader);


void setup() {
    Serial.begin(115200);
    Serial.setTimeout(50);
    sc.set_goal(0);
}

void loop() {
    us_reader.read_sensor();

    // set speed to 0 if too close to object
    if (us_reader.get_distance() < 50 && us_reader.has_lock()) {
        mc.set_speed(0);
    }

    // set speed to 0 if no communication with RP0
    if (digitalRead(CHECK_COMM) != HIGH)
    {
        mc.set_speed(0);
    }

    sc.reach_goal();
}

void serialEvent() {
    if (Serial.available() > 0) {
        bytesRead = scom.readBuffer(buffer, BUFFER_SIZE);  // read serial port into buffer

        byte receivedPackage[bytesRead];  // initiate package byte array
        memcpy(receivedPackage, buffer, bytesRead);  // copy data from buffer to package

        scom.processPackage(receivedPackage, bytesRead);
    }
}
