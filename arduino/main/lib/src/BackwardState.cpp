#include "EngineState.h"
#include "BackwardState.h"
#include "MotorController.h"

BackwardState::BackwardState(MotorController mc) : EngineState(mc) {}

EngineState *BackwardState::act(int setSpeed) {
    if (setSpeed == 0) {
      this->motor_controller.stop();
      Serial.println("StopState");
      return this->ss;//*StopState(this->motor_controller);
    }
    else if (setSpeed < 0) {
      this->motor_controller.backward(setSpeed);
      Serial.println("BackwardState");
      return this;
    }
    else if (setSpeed > 0) { // todo: change this move forward
      this->motor_controller.stop();
      Serial.println("StopState");
      return this->ss;//*StopState(this->motor_controller);

    }
    else {
        Serial.println("BackwardState");
        return this;
    }

};

void BackwardState::setState(EngineState *ss) {
	this->ss = ss;
};
