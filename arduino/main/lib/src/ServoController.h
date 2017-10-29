#ifndef ServoController_h
#define ServoController_h

#include "MotorController.h"

class ServoController {
    public:
        ServoController(MotorController);
        void turn_left();
        void turn_right();
        void reach_goal();
        void set_goal(char direction);
        int goal_diff();
        void stop();
        void break_engine();
        int angle();
        bool overshoot_left();
        bool overshoot_right();
        bool overshoot();
        char get_state();
    protected:
        MotorController motor_controller;
    private:
        char state;
        int goal = 660;
        int current_tol = 5;
};

#endif
