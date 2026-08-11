#include "../ChordedKeyboard/schema.hpp"
#include <cctype>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <random>

bool right_handed_mode = false;

void print_chord(const Chord &_c) {
  std::cout << "Chord:\n";

  // Up row
  if (!right_handed_mode) {
    size_t i = 0;
    for (const auto &cur :
         {_c.pinky, _c.ring, _c.middle, _c.pointer, _c.thumb}) {
      if (i == 4) {
        std::cout << ' ';
      }
      std::cout << (cur == UP ? 'U' : '.');
      ++i;
    }
  } else {
    size_t i = 0;
    for (const auto &cur :
         {_c.pinky, _c.ring, _c.middle, _c.pointer, _c.thumb}) {
      if (i == 1) {
        std::cout << ' ';
      }
      std::cout << (cur == UP ? 'U' : '.');
      ++i;
    }
  }
  std::cout << "\n";

  // Down row
  if (!right_handed_mode) {
    size_t i = 0;
    for (const auto &cur :
         {_c.pinky, _c.ring, _c.middle, _c.pointer, _c.thumb}) {
      if (i == 4) {
        std::cout << ' ';
      }
      std::cout << (cur == DOWN ? 'D' : '.');
      ++i;
    }
  } else {
    size_t i = 0;
    for (const auto &cur :
         {_c.pinky, _c.ring, _c.middle, _c.pointer, _c.thumb}) {
      if (i == 1) {
        std::cout << ' ';
      }
      std::cout << (cur == DOWN ? 'D' : '.');
      ++i;
    }
  }

  std::cout << '\n';
}

void print_key(const int &_k) {
  std::cout << "Key: ";
  switch (_k) {
  case KEY_TAB:
    std::cout << "tab";
    break;
  case KEY_RIGHT_ARROW:
    std::cout << "right arrow";
    break;
  case KEY_UP_ARROW:
    std::cout << "up arrow";
    break;
  case KEY_DOWN_ARROW:
    std::cout << "down arrow";
    break;
  case KEY_HOME:
    std::cout << "home / windows";
    break;
  case KEY_ESC:
    std::cout << "escape";
    break;
  case KEY_LEFT_ARROW:
    std::cout << "left arrow";
    break;
  case KEY_CAPS_LOCK:
    std::cout << "caps lock";
    break;
  case KEY_RETURN:
    std::cout << "return / enter";
    break;
  case KEY_BACKSPACE:
    std::cout << "backspace";
    break;
  default:
    if (std::isprint(_k)) {
      std::cout << '\'' << (char)_k << '\'';
    } else {
      std::cout << _k;
    }
    break;
  }
  std::cout << '\n';
}

int main(int c, char *v[]) {
  std::cout
      << "This is a training program for Jordan Dehmel's "
         "chorded keyboard system. It takes in either zero or "
         "one command line argument (the keyboard schema to "
         "use, with the default being the built-in one), then "
         "randomly prompts the user to input keys (with the "
         "chords being displayed) until it is halted. To exit, "
         "use CTRL+C.\n\n";

  bool saw_fp = false;
  std::filesystem::path fp;
  for (int i = 1; i < c; ++i) {
    const std::string arg = v[i];
    if (arg == "--lefty") {
      right_handed_mode = false;
    } else if (arg == "--righty") {
      right_handed_mode = true;
    } else {
      saw_fp = true;
      fp = arg;
    }
  }

  const Schema s =
      saw_fp ? Schema::from_file(fp) : default_schema;

  // Note: This is inclusive on both sides
  std::uniform_int_distribution<size_t> range(1,
                                              Schema::data_len);
  std::random_device rng;

  while (true) {
    // Choose a random inhabited key
    size_t i;
    do {
      i = range(rng);
    } while (s.get_key(Chord::from_int(i)) == 0);

    const Chord chord = Chord::from_int(i);
    const int key = s.get_key(chord);

    std::cout << '\n';
    print_chord(chord);
    print_key(key);

    if (std::isprint(key)) {
      // Wait until the user inputs that key
      while (true) {
        const char obs = std::cin.get();
        if (obs == key) {
          break;
        }
      }
    } else {
      std::cout << "(enter any key to advance)\n";
      std::cin.get();
    }
    std::cin.ignore(999, '\n');
  }

  return 0;
}
