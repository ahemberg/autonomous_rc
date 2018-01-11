#ifndef MotorController_h
#define MotorController_h

class MotorController {
    public:
        MotorController(
            int input_pin_1, int input_pin_2, int enable_pin
        );
        void stop();
        void forward(char duty);
        void backward(char duty);
        void enable_engine();
        void disable_engine();
        void break_engine();
    private:
        int input_pin_1, input_pin_2, enable_pin;
    protected:
};

#endif
