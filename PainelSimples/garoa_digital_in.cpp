#include "garoa_digital_in.h"


Jumper::Jumper(uint8_t pin, uint8_t pinMode) {
  _pin = pin;
  _closedState = pinMode == INPUT_PULLUP ? LOW : HIGH;
  ::pinMode(pin, pinMode);
}

bool Jumper::isClosed() {
  return digitalRead(_pin) == _closedState;
}


SwitchSPST::SwitchSPST(uint8_t pin, uint8_t onPolarity)
  : _pin(pin), _onPolarity(onPolarity),
    _state(!onPolarity), _lastState(!onPolarity)
{
  begin();
}

void SwitchSPST::begin() {
  if (_onPolarity == LOW) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
#ifdef INPUT_PULLDOWN
    pinMode(_pin, INPUT_PULLDOWN);
#else
    pinMode(_pin, INPUT);
#endif
  }
  _state = digitalRead(_pin);
  _lastState = _state;
}

void SwitchSPST::update() {
  _lastState = _state;
  _state = digitalRead(_pin);
}

bool SwitchSPST::state()      { return _state == _onPolarity; }
bool SwitchSPST::isOn()       { return _state == _onPolarity; }
bool SwitchSPST::isOff()      { return _state != _onPolarity; }
bool SwitchSPST::justChanged() { return _state != _lastState; }

Button::Button(uint8_t pin, uint8_t polarity)
  : _pin(pin), _polarity(polarity),
    _state(!polarity), _lastState(!polarity),
    _alreadyPressed(false), _pressStarted(0)
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
  _lastState = _state;
}

void Button::update() {
  _lastState = _state;
  _state = digitalRead(_pin);

  if (isPressed()) {
    if (!_alreadyPressed) {
      _alreadyPressed = true;
      _pressStarted = millis();
    }
  } else {
    _alreadyPressed = false;
    _pressStarted = 0;
  }
}

bool Button::isPressed()  { return _state == _polarity; }
bool Button::isReleased() { return _state != _polarity; }

bool Button::justPressed() {
  return (_state != _lastState) && (_state == _polarity);
}

bool Button::justReleased() {
  return (_state != _lastState) && (_state != _polarity);
}

bool Button::isHeld(unsigned long int duration) {
  return isPressed() && ((millis() - _pressStarted) >= duration);
}
