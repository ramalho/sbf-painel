#ifndef garoa_button_h
#define garoa_button_h

#include "Arduino.h"

class Jumper {
  public:
    Jumper(uint8_t pin, uint8_t pinMode);
    bool isClosed();
  private:
    uint8_t _pin;
    uint8_t _closedState;
};


class SwitchSPST {
  public:
    SwitchSPST(uint8_t pin, uint8_t onPolarity = LOW);
    void begin();
    void update();
    bool state();
    bool isOn();
    bool isOff();
    bool justChanged();

  private:
    uint8_t _pin;
    bool _onPolarity;
    bool _state;
    bool _lastState;
};

class Button {
  public:
    Button(uint8_t pin, uint8_t polarity = LOW);
    void begin();
    void update();
    bool isPressed();
    bool isReleased();
    bool justPressed();
    bool justReleased();
    bool isHeld(unsigned long int duration);

  private:
    uint8_t _pin;
    bool _polarity;
    bool _state;
    bool _lastState;
    bool _alreadyPressed;
    unsigned long int _pressStarted;
};

#endif
