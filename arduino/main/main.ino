#define TRIG 6
#define ECHO  9

#include "src/ultra_sound_reader.h"
#include "src/StopState.h"
#include "src/ForwardState.h"
#include "src/EngineState.h"
#include "src/MotorController.h"

void setup() {
  Serial.begin(9600); 
  Serial.setTimeout(50);
}

UltraSoundReader us_reader = UltraSoundReader(TRIG,ECHO);
MotorController mc = MotorController();
EngineState *state = new StopState(mc);
bool start = true;
int distance;

void loop() {
	if(start) {
		state = state->act('w');
	} 
  start = false;
 	us_reader.read_sensor();
 	distance = us_reader.get_distance();
 	Serial.println(distance);
 	if(distance < 30) {
 		Serial.println(-10000000);
 		state = state->stop();
 		Serial.println(10000000);
 	}
}
