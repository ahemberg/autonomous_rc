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

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  ss.setState(&fs, &bs);
  fs.setState(&ss);
  bs.setState(&ss);
}

UltraSoundReader us_reader = UltraSoundReader(TRIG,ECHO);

EngineState *current_state = &ss;
char comm;
void loop() {

    if (Serial.available() > 0) {
        comm = Serial.read();
    }

    if (comm == 'z' || comm == 'x' || comm == 'c') {
        sc.set_goal(comm);
        comm = 0;
    } else if (comm == 'w' || comm == 's') {
        current_state = current_state->act(comm);
        comm = 0;
    }

    //if (start) {
        //current_state = current_state->act('w');
        //sc.set_goal('l');
	//}

    sc.reach_goal();
 	us_reader.read_sensor();
 	if (us_reader.has_lock()) {
    Serial.print("DISTANCE: ");
    Serial.print(us_reader.get_distance());
  	} else {
  		Serial.print("NO Lock (");
  		Serial.print(us_reader.get_distance());
  	}

    Serial.print(", DIFF ");
    Serial.print(sc.goal_diff());
    Serial.print(", ANGLE ");
    Serial.print(sc.angle());
    Serial.print("\r\n");

  	if (us_reader.get_distance() < 50 && us_reader.has_lock()) {
 		current_state->stop();
    	current_state = &ss;
 	}



}
