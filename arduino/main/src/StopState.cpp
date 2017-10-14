#include "EngingeState.h"
#include "StopState.h"
#include "ForwardState.h"
#include "BackwardState.h"


EngingeState StopState::act(char command) {
    switch(command) {
        case 'w':
            this.mc.forward();
            return ForwardState(this.mc);
        case 's':
            this.mc.backward();
            return BackwardState(this.mc);
        default:
            return this;
    }
};