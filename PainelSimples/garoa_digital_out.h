#ifndef garoa_digital_io_h
#define garoa_digital_io_h


class DigitalOutput {
  public:
    DigitalOutput(int pin, int signalOn);
    bool isOn();
    void turnOn();
    void turnOff();
    bool toggle();
    void set(bool on);
    void startCycling(unsigned long cycleDuration);
    bool isCycling();
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



class Buzzer {
  public:
    Buzzer(uint8_t pin);
    void start(unsigned int frequency, unsigned long duration_in_ms); // duration 0 = "forever"
    void stop();
    bool isPlaying();
    void update();  // call each loop() to handle auto-stop
  private:
    uint8_t _pin;
    bool _playing;
    unsigned long _stopTime;
    bool _indefinite;
};


#endif
