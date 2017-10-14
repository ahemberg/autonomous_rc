#ifndef EngineState_h
#define EngineState_h

#include "MotorController.h"

class EngineState {
    public:
        EngineState(MotorController);
        virtual EngineState *act(char command);
        EngineState *stop();
    protected:
        MotorController motor_controller;
};

#endif