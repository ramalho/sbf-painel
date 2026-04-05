#include "garoa_button.h"

// Define the button pin - use any GPIO
#define BUTTON_PIN 4

// Create a Button object; pressed when LOW (default polarity)
Button button(BUTTON_PIN, LOW);

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  // Button is initialized in the constructor, nothing extra needed here
}

void loop() {
  // Update the button state, this will do the digitalRead() for us
  // must be called ~every 10ms to keep state and catch presses
  button.update();

  if (button.just_pressed()) {
    Serial.println("Button was just pressed!");
  }
  if (button.just_released()) {
    Serial.println("Button was just released!");
  }

  // Add a small debouncing delay
  delay(10);
}
