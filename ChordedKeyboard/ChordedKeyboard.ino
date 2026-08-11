// Firmware for a 10-key chorded keyboard
// Jordan Dehmel, 2026, MIT license

#include "schema.hpp"
#include <Keyboard.h>

// Put your pins here!
const static int pinky_up_pin = 0;
const static int pinky_down_pin = 0;
const static int ring_up_pin = 0;
const static int ring_down_pin = 0;
const static int middle_up_pin = 0;
const static int middle_down_pin = 0;
const static int pointer_up_pin = 0;
const static int pointer_down_pin = 0;
const static int thumb_up_pin = 0;
const static int thumb_down_pin = 0;
const static int light_pin = 0;

void setup() {
  pinMode(pinky_up_pin, INPUT_PULLUP);
  pinMode(pinky_down_pin, INPUT_PULLUP);
  pinMode(ring_up_pin, INPUT_PULLUP);
  pinMode(ring_down_pin, INPUT_PULLUP);
  pinMode(middle_up_pin, INPUT_PULLUP);
  pinMode(middle_down_pin, INPUT_PULLUP);
  pinMode(pointer_up_pin, INPUT_PULLUP);
  pinMode(pointer_down_pin, INPUT_PULLUP);
  pinMode(thumb_up_pin, INPUT_PULLUP);
  pinMode(thumb_down_pin, INPUT_PULLUP);

  pinMode(light_pin, OUTPUT);
  Keyboard.begin();
}

void loop() {
  Chord state;
  state.pinky = state.ring = state.middle = state.pointer =
      state.thumb = OFF;

  if (digitalRead(pinky_up_pin) == HIGH) {
    state.pinky = UP;
  } else if (digitalRead(pinky_down_pin) == HIGH) {
    state.pinky = DOWN;
  }
  if (digitalRead(ring_up_pin) == HIGH) {
    state.ring = UP;
  } else if (digitalRead(ring_down_pin) == HIGH) {
    state.ring = DOWN;
  }
  if (digitalRead(middle_up_pin) == HIGH) {
    state.middle = UP;
  } else if (digitalRead(middle_down_pin) == HIGH) {
    state.middle = DOWN;
  }
  if (digitalRead(pointer_up_pin) == HIGH) {
    state.pointer = UP;
  } else if (digitalRead(pointer_down_pin) == HIGH) {
    state.pointer = DOWN;
  }
  if (digitalRead(thumb_up_pin) == HIGH) {
    state.thumb = UP;
  } else if (digitalRead(thumb_down_pin) == HIGH) {
    state.thumb = DOWN;
  }

  const int key = default_schema.get_key(state);
  if (key > 0) {
    digitalWrite(light_pin, HIGH);
    Keyboard.press(key);
  } else {
    digitalWrite(light_pin, LOW);
    Keyboard.releaseAll();
  }
}
