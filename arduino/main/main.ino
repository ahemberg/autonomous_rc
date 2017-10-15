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

void loop() {  

	if (start) {
    	current_state = current_state->act('w');
    	//digitalWrite(6, HIGH);
		//digitalWrite(5, LOW);
		//analogWrite(3, 120);
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
 	if (us_reader.has_lock()) {
 		Serial.println(us_reader.get_distance());
  	} else {
  		Serial.print("NO Lock (");
  		Serial.print(us_reader.get_distance());
  		Serial.print(")\r\n");
  	}

  	if (us_reader.get_distance() < 50 && us_reader.has_lock()) {
 		current_state->stop();
    	current_state = &ss;
 	}
}
