#ifndef MotorController_h
#define MotorController_h

class MotorController {
    public:
        void stop();
        void forward();
        void backward();
        void enable_engine();
        void disable_engine();
        void break_engine();
};

#endif