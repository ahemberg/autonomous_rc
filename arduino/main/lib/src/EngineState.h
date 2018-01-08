#ifndef EngineState_h
#define EngineState_h

#include "MotorController.h"

class EngineState {
    public:
        EngineState(MotorController);
        virtual EngineState *act(int setSpeed);
        void stop();
    protected:
        MotorController motor_controller;
};

#endif
