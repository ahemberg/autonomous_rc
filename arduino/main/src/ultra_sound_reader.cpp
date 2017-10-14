
#include "ultra_sound_reader.h"
#include "Arduino.h"


UltraSoundReader::UltraSoundReader(int trigger_pin, int echo_pin) {
	this->trigger = trigger_pin;
	this->echo = echo_pin;
}

void UltraSoundReader::read_sensor() {
	digitalWrite(this->trigger, HIGH); 
    delayMicroseconds(100); 
    digitalWrite(this->trigger, LOW); 
    this->distance = pulseIn(this->echo, HIGH);
}

int UltraSoundReader::get_distance() {
	return this->distance;
}