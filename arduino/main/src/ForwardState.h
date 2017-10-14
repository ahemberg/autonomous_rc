#ifndef ForwardState_h
#define ForwardState_h

#include "EngineState.h"
#include "MotorController.h"

class ForwardState : public EngineState {
public:
	ForwardState(MotorController mc);
	EngineState *act(char command);
};

#endif