#include "garoa_button.h"

Button::Button(uint8_t pin, uint8_t polarity)
  : _pin(pin), _polarity(polarity),
    _state(!polarity), _last_state(!polarity),
    _already_pressed(false), _press_started(0)
{
  begin();
}

void Button::begin() {
  if (_polarity == LOW) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
#ifdef INPUT_PULLDOWN
    pinMode(_pin, INPUT_PULLDOWN);
#else
    pinMode(_pin, INPUT);
#endif
  }
  _state = digitalRead(_pin);
  _last_state = _state;
}

void Button::update() {
  _last_state = _state;
  _state = digitalRead(_pin);

  if (is_pressed()) {
    if (!_already_pressed) {
      _already_pressed = true;
      _press_started = millis();
    }
  } else {
    _already_pressed = false;
    _press_started = 0;
  }
}

bool Button::is_pressed()  { return _state == _polarity; }
bool Button::is_released() { return _state != _polarity; }

bool Button::just_pressed() {
  return (_state != _last_state) && (_state == _polarity);
}

bool Button::just_released() {
  return (_state != _last_state) && (_state != _polarity);
}

bool Button::is_held(unsigned long int duration) {
  return is_pressed() && ((millis() - _press_started) >= duration);
}
