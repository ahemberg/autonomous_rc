/*
 * Some kind of file explanation
 */

class UltraSoundReader {
    private:
        int trigger, echo, distance;
    protected:

    public:
        UltraSoundReader(int trigger_pin, int echo_pin);
        void read_sensor();
        int get_distance();
};
