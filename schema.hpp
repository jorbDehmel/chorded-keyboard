/**
 * @brief Resources for the chorded keyboard
 */

#pragma once

#include <initializer_list>
#include <string>

// Needed since we want to call this from both Arduino and real
// C++
#if not __has_include("Keyboard.h")
#define NOT_ARDUINO
#include <cassert>
#include <filesystem>
#include <fstream>
const static int KEY_TAB = -1;
const static int KEY_RIGHT_ARROW = -2;
const static int KEY_UP_ARROW = -3;
const static int KEY_DOWN_ARROW = -4;
const static int KEY_HOME = -5;
const static int KEY_ESC = -6;
const static int KEY_LEFT_ARROW = -7;
const static int KEY_CAPS_LOCK = -8;
const static int KEY_RETURN = -9;
const static int KEY_BACKSPACE = -10;
#endif

/// The state of a single finger on the chorded keyboard
enum FingerState { UP, OFF, DOWN };

/// A state of a chorded keyboard
struct Chord {
  FingerState pinky, ring, middle, pointer, thumb;

  static Chord from_str(const std::string &_s) {
    Chord out;
    out.pinky = _s[0] == 'U' ? UP : _s[0] == 'D' ? DOWN : OFF;
    out.ring = _s[1] == 'U' ? UP : _s[1] == 'D' ? DOWN : OFF;
    out.middle = _s[2] == 'U' ? UP : _s[2] == 'D' ? DOWN : OFF;
    out.pointer = _s[3] == 'U' ? UP : _s[3] == 'D' ? DOWN : OFF;
    out.thumb = _s[4] == 'U' ? UP : _s[4] == 'D' ? DOWN : OFF;
    return out;
  }

  std::string to_string() const noexcept {
    std::string out;
    out.push_back("U0D"[pinky]);
    out.push_back("U0D"[ring]);
    out.push_back("U0D"[middle]);
    out.push_back("U0D"[pointer]);
    out.push_back("U0D"[thumb]);
    return out;
  }

  static Chord from_int(const size_t &_i) {
    size_t i = _i;
    Chord out;
    out.thumb = static_cast<FingerState>(i % 3);
    i /= 3;
    out.pointer = static_cast<FingerState>(i % 3);
    i /= 3;
    out.middle = static_cast<FingerState>(i % 3);
    i /= 3;
    out.ring = static_cast<FingerState>(i % 3);
    i /= 3;
    out.pinky = static_cast<FingerState>(i % 3);
    return out;
  }

  int to_int() const {
    return thumb + 3 * (pointer +
                        3 * (middle + 3 * (ring + 3 * pinky)));
  }
};

/// A chorded keyboard schema
class Schema {
public:
  /// Initialize from a list of pairs where each pair maps a
  /// chord to its key. Do NOT include the null chord here!
  Schema(
      const std::initializer_list<std::pair<std::string, int>>
          &_table) {
    for (const auto &p : _table) {
      data[Chord::from_str(p.first).to_int() - 1] = p.second;
    }
  }

  /// Return the key that the current chord corresponds to.
  /// If no key, returns 0.
  int get_key(const struct Chord &_state) const noexcept {
    if (_state.thumb == OFF) {
      return 0;
    }
    return data[_state.to_int() - 1];
  }

#ifdef NOT_ARDUINO

  static Schema from_file(const std::filesystem::path &_fp) {
    std::ifstream f(_fp);
    assert(f.is_open());
    Schema out({});
    f.read((char *)&out.data, sizeof(out.data));
    return out;
  }

  void to_file(const std::filesystem::path &_fp) const {
    std::ofstream f(_fp);
    assert(f.is_open());
    f.write((char *)&data, sizeof(data));
  }

#endif

  const static size_t data_len = (3 * 3 * 3 * 3 * 3) - 1;

protected:
  // Treats the configuration as a 5-length ternary number, but
  // subtracts 1 from it (since the null config is used).
  int data[data_len];
};

const static Schema default_schema = {
    {"0000U", KEY_TAB},
    {"000UU", '8'},
    {"000DU", KEY_RIGHT_ARROW},
    {"00U0U", '4'},
    {"00D0U", KEY_UP_ARROW},
    {"0U00U", '2'},
    {"0UU0U", '6'},
    {"0D00U", KEY_DOWN_ARROW},
    {"0DD0U", KEY_HOME},
    {"U000U", '1'},
    {"U00UU", '9'},
    {"U0U0U", '5'},
    {"UU00U", '3'},
    {"UUU0U", '7'},
    {"UUUUU", KEY_ESC},
    {"D000U", KEY_LEFT_ARROW},
    {"DDDDU", KEY_CAPS_LOCK},
    {"0000D", ' '},
    {"000UD", 'r'},
    {"000DD", 'f'},
    {"00U0D", 'e'},
    {"00UUD", KEY_RETURN},
    {"00UDD", 'v'},
    {"00D0D", 'd'},
    {"00DUD", 't'},
    {"00DDD", 'g'},
    {"0U00D", 'w'},
    {"0UU0D", KEY_BACKSPACE},
    {"0UUUD", '0'},
    {"0UD0D", 'c'},
    {"0D00D", 's'},
    {"U000D", 'q'},
    {"U00DD", 'p'},
    {"UD00D", 'x'},
    {"UDUDD", 'z'},
    {"D000D", 'a'},
    {"D00UD", 'u'},
    {"D00DD", 'j'},
    {"D0U0D", 'i'},
    {"D0UDD", 'b'},
    {"D0D0D", 'k'},
    {"D0DUD", 'y'},
    {"D0DDD", 'h'},
    {"DU00D", 'o'},
    {"DUD0D", 'n'},
    {"DUDUD", 'm'},
    {"DD00D", 'l'},
};
