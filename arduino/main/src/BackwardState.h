#ifndef BackwardState_h
#define BackwardState_h

#include "EngineState.h"
#include "StopState.h"
#include "MotorController.h"

class BackwardState : public EngineState {
public:
	BackwardState(MotorController mc, StopState *ss);
	EngineState *act(char command);
};

#endif