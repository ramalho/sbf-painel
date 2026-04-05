#ifndef garoa_button_h
#define garoa_button_h

#include "Arduino.h"

class Button {
  public:
    Button(uint8_t pin, uint8_t polarity = LOW);
    void begin();
    void update();
    bool is_pressed();
    bool is_released();
    bool just_pressed();
    bool just_released();
    bool is_held(unsigned long int duration);

  private:
    uint8_t _pin;
    bool _polarity;
    bool _state;
    bool _last_state;
    bool _already_pressed;
    unsigned long int _press_started;
};

#endif
