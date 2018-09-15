#ifndef UltraSoundReader_h
#define UltraSoundReader_h

class UltraSoundReader {
private:
  bool _lock = false;
  int _trigger, _echo, _distance = 0;

protected:
public:
  UltraSoundReader(int trigger_pin, int echo_pin);
  void read_sensor();
  long get_distance();
  bool has_lock();
};

#endif
