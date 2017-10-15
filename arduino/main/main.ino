#define TRIG 6
#define ECHO  9

#include "src/ultra_sound_reader.h"
#include "src/StopState.h"
#include "src/ForwardState.h"
#include "src/BackwardState.h"
#include "src/EngineState.h"
#include "src/MotorController.h"

MotorController mc = MotorController();
StopState ss = StopState(mc);
ForwardState fs = ForwardState(mc);
BackwardState bs = BackwardState(mc);

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
	} 
  start = false;
 	us_reader.read_sensor();
 	distance = us_reader.get_distance();
 	Serial.println(distance);
 	if(distance < 50) {
 		current_state->stop();
    current_state = &ss;
 	}
}
