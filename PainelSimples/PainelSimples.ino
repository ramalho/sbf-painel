#include "garoa_digital_io.h"
#include "garoa_button.h"

#define LDR_PIN    A0
#define BUZZER_PIN 13
#define RED_PIN    8
#define GREEN_PIN  9
#define BUTTON_PIN 2

OutputOnOff red_led(RED_PIN, HIGH);
OutputOnOff green_led(GREEN_PIN, HIGH);
Button power(BUTTON_PIN, LOW);

bool alerting = false;
bool running = false;

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  power.update();
  if (power.just_pressed()) {
    running = !running;
    green_led.toggle();
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
