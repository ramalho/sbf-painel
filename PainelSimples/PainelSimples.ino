#include "garoa_digital_io.h"
#include "garoa_button.h"

const unsigned int LOOP_DELAY = 10;  // ms; required for debounce

const uint8_t LDR_PIN    = A0;
const uint8_t BUZZER_PIN = 13;
const uint8_t RED_PIN    = 2;
const uint8_t GREEN_PIN  = 3;
const uint8_t BUTTON_PIN = A1;
const uint8_t LINE_RELAY_PIN = 11;


DigitalOutput redLed(RED_PIN, HIGH);
DigitalOutput greenLed(GREEN_PIN, HIGH);
Button powerBtn(BUTTON_PIN, LOW);
DigitalOutput lineRelay(LINE_RELAY_PIN, LOW);
Buzzer buzzer(BUZZER_PIN);

bool lineActive = false;

void setup() {
  pinMode(LDR_PIN, INPUT);
}

void handlePower() {
  if (powerBtn.justPressed()) {
    lineActive = !lineActive;
    greenLed.set(lineActive);
    lineRelay.set(lineActive);
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

void loop() {
  handlePower();
  handleShortCircuit();
  powerBtn.update();  // required for debounce
  redLed.update();    // required to blink
  buzzer.update();    // required for timed tones
  delay(LOOP_DELAY);
}
