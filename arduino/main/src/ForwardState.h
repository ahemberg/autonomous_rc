#ifndef ForwardState_h
#define ForwardState_h

#include "EngineState.h"
#include "StopState.h"
#include "MotorController.h"

class ForwardState : public EngineState {
public:
	ForwardState(MotorController mc, StopState *stop_state);
	EngineState *act(char command);
};

#endif