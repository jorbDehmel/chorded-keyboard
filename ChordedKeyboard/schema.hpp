/**
 * @brief Resources for the chorded keyboard
 */

#pragma once

// Needed since we want to call this from both Arduino and real
// C++
#ifndef ARDUINO
#include <filesystem>
#include <fstream>
using String = std::string;
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
#else
#include <Keyboard.h>
#endif

/// The state of a single finger on the chorded keyboard
enum FingerState {
  UP,  // The up button is pressed
  OFF, // The down button is pressed
  DOWN // Neither button is pressed
};

/// Indicates a str chord instead of a character chord
const static int MULTIKEY = -1024;

/// This is just std::pair<std::string, int>. I miss real C++.
/// (T_T)
struct ChordKeyPair {
  String first;
  int second;
};

/// This is just std::pair<std::string, std::string>.
struct ChordStrPair {
  String first;
  String second;
};

/// A state of a chorded keyboard
struct Chord {
  /// Data
  FingerState pinky, ring, middle, pointer, thumb;

  /// Load from a string
  static Chord from_str(const String &_s) {
    Chord out;
    out.pinky = _s[0] == 'U' ? UP : _s[0] == 'D' ? DOWN : OFF;
    out.ring = _s[1] == 'U' ? UP : _s[1] == 'D' ? DOWN : OFF;
    out.middle = _s[2] == 'U' ? UP : _s[2] == 'D' ? DOWN : OFF;
    out.pointer = _s[3] == 'U' ? UP : _s[3] == 'D' ? DOWN : OFF;
    out.thumb = _s[4] == 'U' ? UP : _s[4] == 'D' ? DOWN : OFF;
    return out;
  }

  /// Encode into an int
  int to_int() const {
    return (thumb == UP ? 0 : 1) + 2 * (pointer +
                        3 * (middle + 3 * (ring + 3 * pinky)));
  }

#ifdef NOT_ARDUINO
  /// Encode into a string
  String to_string() const noexcept {
    String out;
    out.push_back("U0D"[pinky]);
    out.push_back("U0D"[ring]);
    out.push_back("U0D"[middle]);
    out.push_back("U0D"[pointer]);
    out.push_back("U0D"[thumb]);
    return out;
  }

  /// Load from an encode int
  static Chord from_int(const int &_i) {
    size_t i = _i;
    Chord out;
    out.thumb = (i % 2 == 0 ? UP : DOWN);
    i /= 2;
    out.pointer = static_cast<FingerState>(i % 3);
    i /= 3;
    out.middle = static_cast<FingerState>(i % 3);
    i /= 3;
    out.ring = static_cast<FingerState>(i % 3);
    i /= 3;
    out.pinky = static_cast<FingerState>(i % 3);
    return out;
  }
#endif
};

/// A chorded keyboard schema
class Schema {
public:
  /// Initialize from a list of pairs where each pair maps a
  /// chord to its key.
  Schema(const ChordKeyPair *const _table, const size_t &_s,
         const ChordStrPair *const _str_table,
         const size_t &_s2) {
    for (size_t i = 0; i < data_len; ++i) {
      data[i] = 0;
    }

    for (size_t i = 0; i < _s; ++i) {
      data[Chord::from_str(_table[i].first).to_int()] =
          _table[i].second;
    }

    for (size_t i = 0; i < _s2; ++i) {
      const int ind =
          Chord::from_str(_str_table[i].first).to_int();
      data[ind] = MULTIKEY;
      data2[ind] = _str_table[i].second;
    }
  }

  /// Return the key that the current chord corresponds to.
  /// If no key, returns 0.
  int get_key(const struct Chord &_state) const noexcept {
    return data[_state.to_int()];
  }

  /// If get_key returned MULTIKEY, get the str from here
  String multikey(const struct Chord &_state) const noexcept {
    return data2[_state.to_int()];
  }

#ifdef NOT_ARDUINO
  /// Load from a file
  static Schema from_file(const std::filesystem::path &_fp) {
    std::ifstream f(_fp);
    Schema out(nullptr, 0, nullptr, 0);
    f.read((char *)&out.data, sizeof(out.data));
    f.read((char *)&out.data2, sizeof(out.data2));
    return out;
  }

  /// Write to a file
  void to_file(const std::filesystem::path &_fp) const {
    std::ofstream f(_fp);
    f.write((char *)&data, sizeof(data));
    f.write((char *)&data2, sizeof(data2));
  }
#endif

  /// The length of the data block
  const static size_t data_len = 2 * 3 * 3 * 3 * 3;

protected:
  /// Treats the configuration as a 5-"digit" ternary number,
  int data[data_len];

  String data2[data_len];
};

/// To load the default schema from
const static ChordKeyPair l[] = {
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
    {"DUDDD", 'z'},
    {"D000D", 'a'},
    {"D00UD", 'u'},
    {"D00DD", 'j'},
    {"0DU0D", 'i'},
    {"0DU0U", 'I'},
    {"D0UDD", 'b'},
    {"D0D0D", 'k'},
    {"D0DUD", 'y'},
    {"D0DDD", 'h'},
    {"DU00D", 'o'},
    {"DUD0D", 'n'},
    {"0DUDU", 'm'},
    {"DD00D", 'l'},
    {"UUUUD", '|'},
    {"UUUDD", '['},
    {"UU0UD", ';'},
    {"UU00D", ','},
    {"UUDDD", '/'},
    {"U0UUD", '!'},
    {"U0U0D", '#'},
    {"U0UDD", '?'},
    {"U00UD", ':'},
    {"UDUUD", '$'},
    {"UDDUD", ')'},
    {"UDDDD", '}'},
    {"0UUDD", '<'},
    {"0U0UD", '='},
    {"0UDDD", '+'},
    {"0DUUD", '*'},
    {"0DUDD", '^'},
    {"0DDUD", '>'},
    {"0DD0D", '_'},
    {"DUUUD", '{'},
    {"DUUDD", '('},
    {"DUDUD", '~'},
    {"DDUUD", '\\'},
    {"DDU0D", '.'},
    {"DDDUD", ']'},
    {"DDD0D", '&'},
    {"UUDDU", '%'},
    {"00UUU", '-'},
    {"00UDU", '`'},
    {"00DUU", '\''},
    {"00DDU", '"'},
    {"D00UU", '@'},
};

const static ChordStrPair l2[] = {
    {"UU0DD", "gr"},  {"DU0DD", "ow"},  {"D0U0D", "ng"},
    {"DDUDD", "in"},  {"DD0DD", "nd"},  {"DDDDD", "ing"},
    {"UDDUU", "thr"}, {"DUUDU", "the"}, {"DU0UU", "ou"},
    {"DUDUU", "tr"},  {"DUDDU", "ch"},  {"D00DU", "ai"},
    {"D0DUU", "th"},  {"DDDUU", "sh"},  {"DDD0U", "and"},
};

/// The default schema
const static Schema default_schema(l, sizeof(l) / sizeof(l[0]),
                                   l2,
                                   sizeof(l2) / sizeof(l2[0]));

/*
Bonus chords:
UUU0 D - ctrl + backspace
UUD0 D -
UDU0 D -
UD0U D -
UD0D D -
UDD0 D -
0U0D D -
0UDU D -
0D0U D -
0D0D D -
0DDD D -
DUU0 D -
DU0U D -
UUUD U -
UU0U U -
UU0D U -
UUDU U -
UUD0 U -
UDUU U -
UDU0 U -
UDUD U -
UD00 U -
UD0D U -
UDD0 U -
UDDD U -
0UUU U -
0UUD U -
0U0U U -
0U0D U -
0UDU U -
0UD0 U -
0UDD U -
0DUU U -
0D0U U -
0D0D U -
0DDU U -
0DDD U -
DUUU U -
DUU0 U -
DU00 U -
DU0D U -
DUD0 U -
D0UU U -
D0U0 U -
D0UD U -
D0D0 U -
D0DD U -
DDUU U -
DDU0 U -
DDUD U -
DD0U U -
DD00 U -
DD0D U -
U0UU U -
U00D U -
*/
