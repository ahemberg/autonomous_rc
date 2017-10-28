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
bool start = true;

void loop() {

	if (start) {
    	current_state = current_state->act('w');
      sc.set_goal('l');
	}

	start = false;
  sc.reach_goal();
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
