#ifndef BackwardState_h
#define BackwardState_h

#include "EngineState.h"
#include "MotorController.h"

class BackwardState : public EngineState {
public:
	BackwardState(MotorController mc);
	EngineState *act(int setSpeed);
	void setState(EngineState *ss);
	EngineState *ss;
};

#endif
