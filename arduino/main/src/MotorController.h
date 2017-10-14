#ifndef MotorController_h
#define MotorController_h

class MotorController {
    public:
        void stop();
        void forward();
        void backward();
        void enable_engines();
        void disable_engines();
    private:
        MotorController motor_controller;
};

#endif