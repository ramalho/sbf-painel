/*
 * Copyright (c) 2026 Garoa Hacker Clube
 * Licensed under MIT License
 * 
 * Demonstração de botão com debounce por software.
 * Cada toque no botão acende um led diferente,
 * ou muda a cor de um led RGB (que na verdade é 3 leds).
 * 
 * Este exemplo exige 1 botão e 3 leds ou 1 led RGB de
 * catodo comum: cada led acende no sinal HIGH.
 * 
 * Se você tiver menos de 3 leds, remova itens da constante LEDS.
 * 
 */

#include "garoa_button.h"

#define BUTTON_PIN 2
#define RED_PIN    8
#define GREEN_PIN  9
#define BLUE_PIN   10

// construtor de Button; isso já configura o modo do pino.
Button button(BUTTON_PIN, LOW);

const uint8_t LEDS[] = {RED_PIN, GREEN_PIN, BLUE_PIN};
const uint8_t LEN_LEDS = sizeof(LEDS) / sizeof(LEDS[0]);
uint8_t colorIndex = 0;

void setColor(uint8_t index) {
  for (uint8_t i = 0; i < LEN_LEDS; i++)
    digitalWrite(LEDS[i], i == index ? HIGH : LOW);
}

void setup() {
  // a configuração do pino do button acontece no construtor
  for (uint8_t i = 0; i < LEN_LEDS; i++)
    pinMode(LEDS[i], OUTPUT);
  setColor(colorIndex);
}

void loop() {
  button.update(); // necessário invocar toda volta do laço

  if (button.just_pressed()) { // botão foi pressionado agorinha?
    // somar 1 em LEN_LEDS para ter um estado desligado
    colorIndex = (colorIndex + 1) % (LEN_LEDS + 1);
    setColor(colorIndex);
  }

  delay(10); // importante para que o debounce funcione
}
