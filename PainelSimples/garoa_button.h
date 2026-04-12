#ifndef garoa_button_h
#define garoa_button_h

#include "Arduino.h"

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
