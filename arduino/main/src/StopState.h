#ifndef StopState_h
#define StopState_h

#include "EngineState.h"
#include "MotorController.h"

class StopState : virtual public EngineState {
public:
	StopState(MotorController mc);
	EngineState *act(char command);	
};

#endif