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

DigitalOutput::DigitalOutput(int pin, int signalOn) {
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

bool DigitalOutput::isOn() {
  return _on;
}

void DigitalOutput::turnOn() {
  digitalWrite(_pin, _signalOn);
  _on = true;
}

void DigitalOutput::turnOff() {
  digitalWrite(_pin, _signalOff);
  _on = false;
}

void DigitalOutput::set(bool on) {
  if (on) turnOn();
  else turnOff();
}

bool DigitalOutput::toggle() {
  if (_on) turnOff();
  else turnOn();
  return _on;
}

bool DigitalOutput::isCycling() {
  return _cycling;
}

void DigitalOutput::startCycling(unsigned long cycleDuration) {
  _cycleDuration = cycleDuration;
  _cycling = true;
  _cycleCount = 0;
  _cycleStartTime = millis();
}

int DigitalOutput::update() {
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

void DigitalOutput::stopCycling() {
  _cycling = false;
  turnOff();
}


/************************************************************** Buzzer class */

Buzzer::Buzzer(uint8_t pin) {
  _pin = pin;
  _playing = false;
  _indefinite = false;
  _stopTime = 0;
}

void Buzzer::start(unsigned int frequency, unsigned long duration) {
  tone(_pin, frequency);
  _playing = true;
  _indefinite = (duration == 0);
  _stopTime = millis() + duration;
}

void Buzzer::stop() {
  noTone(_pin);
  _playing = false;
}

bool Buzzer::isPlaying() {
  return _playing;
}

void Buzzer::update() {
  if (_playing && !_indefinite && millis() >= _stopTime)
    stop();
}

