#include "EngineState.h"
#include "ForwardState.h"
#include "StopState.h"


EngingeState ForwardState::act(char command) {
	switch(command) {
		case 'w':
		   return this;
		case 's':
		   this.mc.stop();
		   return StopState(this.mc);
		default:
			return this;
	}
};