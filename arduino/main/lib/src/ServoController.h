#ifndef ServoController_h
#define ServoController_h

class ServoController {
    public:
        ServoController(
            int pwm_pin, int enable_pin, int in1_pin, int in2_pin, char duty,
            int analog_pin
        );
        void set_goal(int new_direction);
        int get_direction();
        void reach_goal();
        void stop();

    private:
        int _pwm_pin, _enable_pin, _in1_pin, _in2_pin, _analog_pin, _goal, _direction;
        char _duty;
        void enable_servo();
        void disable_servo();
        void servo_left();
        void servo_right();
        void servo_stop();
        void turn_left();
        void turn_right();
        int goal_diff();
        int angle();
        bool overshoot_left();
        bool overshoot_right();
        bool overshoot();
    protected:
};

#endif
