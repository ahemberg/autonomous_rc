#include "EngineState.h"
#include "BackwardState.h"
#include "MotorController.h"

BackwardState::BackwardState(MotorController mc) : EngineState(mc) {}

EngineState *BackwardState::act(int setSpeed) {
    if (setSpeed == 0) {
      this->motor_controller.stop();
      return this->ss;//*StopState(this->motor_controller);
    }
    else if (setSpeed < 0) {
      this->motor_controller.backward(setSpeed);
      return this;
    }
    else if (setSpeed > 0) { // todo: change this move forward
      this->motor_controller.stop();
      return this->ss;//*StopState(this->motor_controller);
    }
    else {
      return this;
    }

};

void BackwardState::setState(EngineState *ss) {
	this->ss = ss;
};
