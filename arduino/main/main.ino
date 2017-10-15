#define TRIG 11
#define ECHO  12

#include "src/UltraSoundReader.h"
#include "src/StopState.h"
#include "src/ForwardState.h"
#include "src/BackwardState.h"
#include "src/EngineState.h"
#include "src/MotorController.h"
#include "src/ServoController.h"

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
bool start = true;
int distance;

void loop() {
	if(start) {
		current_state = current_state->act('w');
		// sc.turn_left();
	} 
	// if(sc.get_state() == 'l') {
	// 	if(sc.overshoot_left()) {
	// 		sc.turn_right();
	// 	}
	// } else if(sc.get_state() == 'r') {
	// 	if(sc.overshoot_right()) {
	// 		sc.turn_left();
	// 	}
	// }

  	start = false;
 	us_reader.read_sensor();
 	distance = us_reader.get_distance();
 	Serial.println(distance);
// 	if(distance < 50) {
// 		current_state->stop();
//    current_state = &ss;
// 	}
}
