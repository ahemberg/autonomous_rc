#ifndef MotorController_h
#define MotorController_h

class MotorController {
    public:
        MotorController(
            int input_pin_1, int input_pin_2, int enable_pin
        );
        void set_speed(signed char new_speed);
        signed char get_speed();
        void stop();
        void break_engine();
    private:
        int _input_pin_1, _input_pin_2, _enable_pin;
        signed char _speed;
        void forward(char duty);
        void backward(char duty);
        void enable_engine();
        void disable_engine();
    protected:
};

#endif
