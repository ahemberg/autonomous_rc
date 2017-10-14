#include "EngingeState.h"
#include "BackwardState.h"
#include "StopState.h"


EngingeState BackwardState::act(char command) {
    switch(command) {
        case 'w':
            this.mc.stop();
            return StopState(this.mc);
        case 's':
            return this;
        default:
            return this;
    }
};