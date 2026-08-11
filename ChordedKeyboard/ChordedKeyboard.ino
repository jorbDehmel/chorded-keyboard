#include <Keyboard.h>
#include "schema.hpp"

const static int pinky_up_pin = 13;
const static int pinky_down_pin = 12;
const static int ring_up_pin = 14;
const static int ring_down_pin = 27;
const static int middle_up_pin = 26;
const static int middle_down_pin = 25;
const static int pointer_up_pin = 33;
const static int pointer_down_pin = 32;
const static int thumb_up_pin = 35;
const static int thumb_down_pin = 34;
const static int light_pin = 23;

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

// Given the current state, return what key should
// be sent, or -1 if none. There are 3^4 * 2 chords,
// since the thumb must always engage and the other
// four fingers each have three states. The string
// "0UD0U" here means pinky off, ring up, middle
// down, pointer off, thumb up. Read it like a left
// hand.
int get_key(const struct Chord &_state) {
  switch (_state.thumb) {
  case OFF:
    return -1;
  case UP:
    switch (_state.pinky) {
    case OFF:
      switch (_state.ring) {
      case OFF:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // 0000 U - 0
            return KEY_TAB;
          case UP:
            // 000U U - 8
            return '8';
          case DOWN:
            // 000D U - right arrow
            return KEY_RIGHT_ARROW;
          }
        case UP:
          switch (_state.pointer) {
          case OFF:
            // 00U0 U - 4
            return '4';
          default:
            return -1;
          }
        case DOWN:
          switch (_state.pointer) {
          case OFF:
            // 00D0 U - up arrow
            return KEY_UP_ARROW;
          default:
            return -1;
          }
        }
      case UP:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // 0U00 U - 2
            return '2';
          default:
            return -1;
          }
        case UP:
          switch (_state.pointer) {
          case OFF:
            // 0UU0 U - 6
            return '6';
          default:
            return -1;
          }
        case DOWN:
          return -1;
        }
      case DOWN:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // 0D00 U - down arrow
            return KEY_DOWN_ARROW;
          default:
            return -1;
          }
        case DOWN:
          switch (_state.pointer) {
          case OFF:
            // 0DD0 U - windows
            return KEY_HOME;
          default:
            return -1;
          }
        default:
          return -1;
        }
      }
    case UP:
      switch (_state.ring) {
      case OFF:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // U000 U - 1
            return '1';
          case UP:
            // U00U U - 9
            return '9';
          case DOWN:
            return -1;
          }
        case UP:
          switch (_state.pointer) {
          case OFF:
            // U0U0 U - 5
            return '5';
          default:
            return -1;
          }
        case DOWN:
          return -1;
        }
      case UP:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // UU00 U - 3
            return '3';
          default:
            return -1;
          }
        case UP:
          switch (_state.pointer) {
          case OFF:
            // UUU0 U - 7
            return KEY_UP_ARROW;
            return '7';
          case UP:
            // UUUU U - escape
            return KEY_ESC;
          case DOWN:
            return -1;
          }
        case DOWN:
          return -1;
        }
      case DOWN:
        return -1;
      }
    case DOWN:
      switch (_state.ring) {
      case OFF:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // D000 U - left arrow
            return KEY_LEFT_ARROW;
          case UP:
            return -1;
          case DOWN:
            // D00D U - ctrl
            // return KEY_CTRL;
            return -1;
          }
        default:
          return -1;
        }
      case UP:
        return -1;
      case DOWN:
        switch (_state.middle) {
        case DOWN:
          switch (_state.pointer) {
          case DOWN:
            // DDDD U - caps lock
            return KEY_CAPS_LOCK;
          default:
            return -1;
          }
        default:
          return -1;
        }
      }
    }
  case DOWN:
    switch (_state.pinky) {
    case OFF:
      switch (_state.ring) {
      case OFF:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // 0000 D - space
            return ' ';
          case UP:
            // 000U D - r
            return 'r';
          case DOWN:
            // 000D D - f
            return 'f';
          }
        case UP:
          switch (_state.pointer) {
          case OFF:
            // 00U0 D - e
            return 'e';
          case UP:
            // 00UU D - enter
            return KEY_RETURN;
          case DOWN:
            // 00UD D - v
            return 'v';
          }
        case DOWN:
          switch (_state.pointer) {
          case OFF:
            // 00D0 D - d
            return 'd';
          case UP:
            // 00DU D - t
            return 't';
          case DOWN:
            // 00DD D - g
            return 'g';
          }
        }
      case UP:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // 0U00 D - w
            return 'w';
          case UP:
            return -1;
          case DOWN:
            return -1;
          }
        case UP:
          switch (_state.pointer) {
          case OFF:
            // 0UU0 D - backspace
            return KEY_BACKSPACE;
          case UP:
            // 0UUU D - 0
            return '0';
          case DOWN:
            return -1;
          }
        case DOWN:
          // 0UD0 D - c
          switch (_state.pointer) {
          case OFF:
            return 'c';
          default:
            return -1;
          }
        }
      case DOWN:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // 0D00 D - s
            return 's';
          default:
            return -1;
          }
        default:
          return -1;
        }
      }
    case UP:
      switch (_state.ring) {
      case OFF:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // U000 D - q
            return 'q';
          case UP:
            return -1;
          case DOWN:
            // U00D D - p
            return 'p';
          }
        default:
          return -1;
        }
      case UP:
        return -1;
      case DOWN:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // UD00 D - x
            return 'x';
          default:
            return -1;
          }
        case UP:
          switch (_state.pointer) {
          case DOWN:
            // UDUD D - z
            return 'z';
          default:
            return -1;
          }
        case DOWN:
          return -1;
        }
      }
    case DOWN:
      switch (_state.ring) {
      case OFF:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // D000 D - a
            return 'a';
          case UP:
            // D00U D - u
            return 'u';
          case DOWN:
            // D00D D - j
            return 'j';
          }
        case UP:
          switch (_state.pointer) {
          case OFF:
            // D0U0 D - i
            return 'i';
          case UP:
            return -1;
          case DOWN:
            // D0UD D - b
            return 'b';
          }
        case DOWN:
          switch (_state.pointer) {
          case OFF:
            // D0D0 D - k
            return 'k';
          case UP:
            // D0DU D - y
            return 'y';
          case DOWN:
            // D0DD D - h
            return 'h';
          }
        }
      case UP:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // DU00 D - o
            return 'o';
          default:
            return -1;
          }
        case UP:
          return -1;
        case DOWN:
          switch (_state.pointer) {
          case OFF:
            // DUD0 D - n
            return 'n';
          case UP:
            // DUDU D - m
            return 'm';
          case DOWN:
            return -1;
          }
        }
      case DOWN:
        switch (_state.middle) {
        case OFF:
          switch (_state.pointer) {
          case OFF:
            // DD00 D - l
            return 'l';
          default:
            return -1;
          }
        default:
          return -1;
        }
      }
    }
  }
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
