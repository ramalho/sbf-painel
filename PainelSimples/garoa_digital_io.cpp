#include "Arduino.h"
#include "garoa_digital_io.h"

/************************************************************* Jumper class */

Jumper::Jumper(uint8_t pin, uint8_t pinMode) {
  _pin = pin;
  _closedState = pinMode == INPUT_PULLUP ? LOW : HIGH;
  ::pinMode(pin, pinMode);
}

bool Jumper::isClosed() {
  return digitalRead(_pin) == _closedState;
}

/******************************************************** OutputOnOff class */

OutputOnOff::OutputOnOff(int pin, int signalOn) {
  _pin = pin;
  _signalOn = signalOn;
  _signalOff = signalOn == HIGH ? LOW : HIGH;
  _on = false;
  _cycling = false;
  _cycleCount = 0;
  _cycleStartTime = 0;
  _cycleDuration = 0;

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _signalOff);
}

bool OutputOnOff::isOn() {
  return _on;
}

void OutputOnOff::turnOn() {
  digitalWrite(_pin, _signalOn);
  _on = true;
}

void OutputOnOff::turnOff() {
  digitalWrite(_pin, _signalOff);
  _on = false;
}

bool OutputOnOff::toggle() {
  if (_on) turnOff();
  else turnOn();
  return _on;
}

void OutputOnOff::startCycling(unsigned long cycleDuration) {
  _cycleDuration = cycleDuration;
  _cycling = true;
  _cycleCount = 0;
  _cycleStartTime = millis();
}

int OutputOnOff::update() {
  // update state of device and
  // return cycle_count
  if (!_cycling) return 0;
  unsigned long halfCycle = _cycleDuration / 2;
  if ((millis() - _cycleStartTime) >= halfCycle) {
    _cycleStartTime = millis();
    toggle();
    if (_on) _cycleCount++;
  }
  return _cycleCount;
}

void OutputOnOff::stopCycling() {
  _cycling = false;
  turnOff();
}


