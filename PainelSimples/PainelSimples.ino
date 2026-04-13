#include "garoa_digital_io.h"
#include "garoa_button.h"

const unsigned int LOOP_DELAY = 10;  // ms; required for debounce

const uint8_t LDR_PIN    = A0;
const uint8_t BUZZER_PIN = 13;
const uint8_t RED_PIN    = 2;
const uint8_t GREEN_PIN  = 3;
const uint8_t MAIN_TRACK_BUTTON_PIN = A1;
const uint8_t MAIN_TRACK_RELAY_PIN = 11;
const uint8_t REVERSE_INPUT_PIN = A2;
const uint8_t REVERSE_RELAY_PIN = 9;


DigitalOutput redLed(RED_PIN, HIGH);
DigitalOutput greenLed(GREEN_PIN, HIGH);
Button powerBtn(MAIN_TRACK_BUTTON_PIN, LOW);
DigitalOutput mainTrackRelay(MAIN_TRACK_RELAY_PIN, LOW);
Button reverseInput(REVERSE_INPUT_PIN, LOW);
DigitalOutput reverseRelay(REVERSE_RELAY_PIN, LOW);
Buzzer buzzer(BUZZER_PIN);

bool lineActive = false;
bool reverseActive = false;

void handlePower();
void handleReverse();
void handleShortCircuit();

void setup() {
  pinMode(LDR_PIN, INPUT);
}

void updateControls() {
  powerBtn.update();    // required for debounce
  reverseInput.update();  // required for debounce
  redLed.update();      // required to blink on background
  buzzer.update();      // required for timed tones
}

void loop() {
  handlePower();
  handleReverse();
  handleShortCircuit();
  updateControls();
  delay(LOOP_DELAY);
}

void handlePower() {
  if (powerBtn.justPressed()) {
    lineActive = !lineActive;
    greenLed.set(lineActive);
    mainTrackRelay.set(lineActive);
  }
}

void handleReverse() {
  if (reverseInput.justPressed()) {
    reverseActive = !reverseActive;
    reverseRelay.set(reverseActive);
  }
}

void handleShortCircuit() {
  if (digitalRead(LDR_PIN) == LOW) {
    if (!redLed.isCycling()) {
      redLed.startCycling(200);  // 5 Hz
      greenLed.turnOff();
      buzzer.start(900, 0);  // indefinite
    }
  } else {
    if (redLed.isCycling()) {
      redLed.stopCycling();
      redLed.turnOff();
      buzzer.stop();
      if (lineActive)
        greenLed.turnOn();
    }
  }
}
