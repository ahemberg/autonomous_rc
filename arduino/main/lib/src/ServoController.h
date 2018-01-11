#ifndef ServoController_h
#define ServoController_h

class ServoController {
    public:
        ServoController(
            int pwm_pin, int enable_pin, int in1_pin, int in2_pin, char duty,
            int analog_pin
        );
        void enable_servo();
        void disable_servo();
        void servo_left();
        void servo_right();
        void servo_stop();
        void turn_left();
        void turn_right();
        void set_goal(int direction);
        void reach_goal();
        void stop();
        int angle();
        int goal_diff();
        bool overshoot_left();
        bool overshoot_right();
        bool overshoot();
        int goal;
    private:
        int pwm_pin, enable_pin, in1_pin, in2_pin, analog_pin;
        char duty;
    protected:
};

#endif
