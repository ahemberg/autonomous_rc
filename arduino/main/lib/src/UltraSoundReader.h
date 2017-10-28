/*
 * Some kind of file explanation
 */

class UltraSoundReader {
    private:
    	bool lock = false;
        int trigger, echo, distance = 0;
    protected:

    public:
        UltraSoundReader(int trigger_pin, int echo_pin);
        void read_sensor();
        long get_distance();
        bool has_lock();
};
