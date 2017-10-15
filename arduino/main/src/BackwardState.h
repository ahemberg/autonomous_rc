#ifndef BackwardState_h
#define BackwardState_h

#include "EngineState.h"
#include "MotorController.h"

class BackwardState : public EngineState {
public:
	BackwardState(MotorController mc);
	EngineState *act(char command);
	void setState(EngineState *ss);
	EngineState *ss;
};

#endif