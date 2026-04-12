#ifndef garoa_digital_io_h
#define garoa_digital_io_h


class Jumper {
  public:
    Jumper(uint8_t pin, uint8_t pinMode);
    bool isClosed();
  private:
    uint8_t _pin;
    uint8_t _closedState;
};


class OutputOnOff {
  public:
    OutputOnOff(int pin, int signalOn);
    bool isOn();
    void turnOn();
    void turnOff();
    bool toggle();
    void startCycling(unsigned long cycleDuration);
    int update();
    void stopCycling();
  private:
    int _pin;
    bool _on;
    int _signalOn;
    int _signalOff;
    bool _cycling;
    int _cycleCount;
    unsigned long _cycleStartTime;
    unsigned long _cycleDuration;
};



#endif
