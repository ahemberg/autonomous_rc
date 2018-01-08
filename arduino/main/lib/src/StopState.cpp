#include "EngineState.h"
#include "StopState.h"
#include "MotorController.h"

StopState::StopState(MotorController mc) : EngineState(mc) {}

EngineState *StopState::act(int setSpeed) {
    Serial.println("StopState");
    if (setSpeed > 0) {
      this->motor_controller.forward(setSpeed);
      Serial.println("ForwardState");
      return this->fs;//ForwardState(this->motor_controller);
    }
    else if (setSpeed < 0) {
      this->motor_controller.backward(setSpeed);
      Serial.println("BackwardState");
      return this->bs;//BackwardState(this->motor_controller);
    }
    else {
        Serial.println("StopState");
      return this;
    }
}

void StopState::setState(EngineState *fs, EngineState *bs) {
    this->fs = fs;
    this->bs = bs;
}
