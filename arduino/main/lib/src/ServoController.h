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
        int pwm_pin, enable_pin, in1_pin, in2_pin, analog_pin, goal, direction;
        char duty;
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
