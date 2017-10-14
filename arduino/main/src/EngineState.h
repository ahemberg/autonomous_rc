#ifndef EngineState_h
#define EngineState_h

class EngineState {
    public:
        EngineState(MotorController mc) : motor_controller(mc)
        EngineState act(char command);
    private:
        MotorController motor_controller;
};

#endif