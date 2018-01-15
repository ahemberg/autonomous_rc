
#include "UltraSoundReader.h"
#include "Arduino.h"


UltraSoundReader::UltraSoundReader(int trigger_pin, int echo_pin) {
	pinMode(echo_pin, INPUT);
    pinMode(trigger_pin, OUTPUT);
	this->trigger = trigger_pin;
	this->echo = echo_pin;
}

void UltraSoundReader::read_sensor() {
	digitalWrite(this->trigger, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigger, LOW);
    this->distance = pulseIn(this->echo, HIGH, 50000);

    if (this->distance <= 0) {
    	lock = false;
	} else {
		lock = true;
	}
}

long UltraSoundReader::get_distance() {
	return (long)(this->distance) / 58.138;
}

bool UltraSoundReader::has_lock() {
	return lock;
}
