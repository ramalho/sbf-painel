#include "garoa_digital_io.h"
#include "garoa_button.h"

const uint8_t LDR_PIN    = A0;
const uint8_t BUZZER_PIN = 13;
const uint8_t RED_PIN    = 2;
const uint8_t GREEN_PIN  = 3;
const uint8_t BUTTON_PIN = A1;
const uint8_t LINE_RELAY_PIN = 11;


OutputOnOff red_led(RED_PIN, HIGH);
OutputOnOff green_led(GREEN_PIN, HIGH);
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
  if (powerBtn.just_pressed()) {
    running = !running;
    green_led.toggle();
    if (green_led.is_on()) lineRelay.turn_on();
    else lineRelay.turn_off();
  }

  if (digitalRead(LDR_PIN) == LOW) {
    if (!alerting) {
      alerting = true;
      red_led.start_cycling(200);  // 5 Hz
      green_led.turn_off();
    }
    tone(BUZZER_PIN, 900, 170);
  } else {
    if (alerting) {
      alerting = false;
      red_led.stop_cycling();
      red_led.turn_off();
      if (running)
        green_led.turn_on();
    }
  }
  red_led.update();
  delay(10);
}
