#ifndef ServoController_h
#define ServoController_h

#include "MotorController.h"

class ServoController {
    public:
        ServoController(MotorController);
        void turn_left();
        void turn_right();
        void stop();
        void break_engine();
        int angle();
        bool overshoot_left();
        bool overshoot_right();
        bool overshoot();
    protected:
        MotorController motor_controller;
};

#endif