#ifndef StopState_h
#define StopState_h

#include "EngineState.h"
#include "ForwardState.h"
#include "BackwardState.h"
#include "MotorController.h"

class StopState : public EngineState {
public:
	StopState(MotorController mc, ForwardState *fs, BackwardState *bs);
	EngineState *act(char command);	
};

#endif