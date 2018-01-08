#ifndef StopState_h
#define StopState_h

#include "EngineState.h"
#include "MotorController.h"

class StopState : public EngineState {
public:
	StopState(MotorController mc);
	EngineState *act(int setSpeed);
	void setState(EngineState *fs, EngineState *bs);
	EngineState *fs;
	EngineState *bs;
};

#endif
