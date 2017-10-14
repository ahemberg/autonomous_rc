#define TRIG 6
#define ECHO  9

#include "src/ultra_sound_reader.h"

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
}

UltraSoundReader us_reader = UltraSoundReader(1,2);

void loop() {
  // put your main code here, to run repeatedly:
  us_reader.read_sensor();
  Serial.println(us_reader.get_distance());
}
