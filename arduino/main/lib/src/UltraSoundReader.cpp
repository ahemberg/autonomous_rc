
#include "UltraSoundReader.h"
#include "Arduino.h"


UltraSoundReader::UltraSoundReader(int trigger_pin, int echo_pin) : _trigger(trigger_pin), _echo(echo_pin){
	pinMode(echo_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
}

void UltraSoundReader::read_sensor() {
	digitalWrite(_trigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(_trigger, LOW);
  _distance = pulseIn(_echo, HIGH, 50000);

  if (_distance <= 0) {
		_lock = false;
	} else {
		_lock = true;
	}
}

long UltraSoundReader::get_distance() {
	return (long)(_distance) / 58.138;
}

bool UltraSoundReader::has_lock() {
	return _lock;
}
