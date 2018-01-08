#include "EngineState.h"
#include "StopState.h"
#include "MotorController.h"

StopState::StopState(MotorController mc) : EngineState(mc) {}

EngineState *StopState::act(int setSpeed) {
    if (setSpeed > 0) {
      this->motor_controller.forward(setSpeed);
      return this->fs;//ForwardState(this->motor_controller);
    }
    else if (setSpeed < 0) {
      this->motor_controller.backward(setSpeed);
      return this->bs;//BackwardState(this->motor_controller);
    }
    else {
      return this;
    }
}

void StopState::setState(EngineState *fs, EngineState *bs) {
    this->fs = fs;
    this->bs = bs;
}
