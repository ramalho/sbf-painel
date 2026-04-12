#include "garoa_digital_io.h"
#include "garoa_button.h"

const uint8_t LDR_PIN    = A0;
const uint8_t BUZZER_PIN = 13;
const uint8_t RED_PIN    = 2;
const uint8_t GREEN_PIN  = 3;
const uint8_t BUTTON_PIN = A1;
const uint8_t LINE_RELAY_PIN = 11;


OutputOnOff redLed(RED_PIN, HIGH);
OutputOnOff greenLed(GREEN_PIN, HIGH);
Button powerBtn(BUTTON_PIN, LOW);
OutputOnOff lineRelay(LINE_RELAY_PIN, LOW);

bool alerting = false;
bool running = false;

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  powerBtn.update();
  if (powerBtn.justPressed()) {
    running = !running;
    greenLed.toggle();
    if (greenLed.isOn()) lineRelay.turnOn();
    else lineRelay.turnOff();
  }

  if (digitalRead(LDR_PIN) == LOW) {
    if (!alerting) {
      alerting = true;
      redLed.startCycling(200);  // 5 Hz
      greenLed.turnOff();
    }
    tone(BUZZER_PIN, 900, 170);
  } else {
    if (alerting) {
      alerting = false;
      redLed.stopCycling();
      redLed.turnOff();
      if (running)
        greenLed.turnOn();
    }
  }
  redLed.update();
  delay(10);
}
