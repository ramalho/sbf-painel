#ifndef garoa_digital_io_h
#define garoa_digital_io_h


class Jumper {
  public:
    Jumper(uint8_t pin, uint8_t pin_mode);
    bool is_closed();
  private:
    uint8_t _pin;
    uint8_t _closed_state;
};


class OutputOnOff {
  public:
    OutputOnOff(int pin, int signal_on);
    bool is_on();
    void turn_on();
    void turn_off();
    bool toggle();
    void start_cycling(unsigned long cycle_duration);
    int update();
    void stop_cycling();
  private:
    int _pin;
    bool _on;
    int _signal_on;
    int _signal_off;
    bool _cycling;
    int _cycle_count;
    unsigned long _cycle_start_time;
    unsigned long _cycle_duration;
};



#endif
