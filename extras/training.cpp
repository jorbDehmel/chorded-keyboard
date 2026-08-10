#include "../schema.hpp"
#include <cctype>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <random>

int main(int c, char *v[]) {
  std::cout
      << "This is a training program for Jordan Dehmel's "
         "chorded keyboard system. It takes in either zero or "
         "one command line argument (the keyboard schema to "
         "use, with the default being the built-in one), then "
         "randomly prompts the user to input keys (with the "
         "chords being displayed) until it is halted. To exit, "
         "use CTRL+C.\n\n";

  const Schema s =
      c > 1 ? Schema::from_file(v[1]) : default_schema;

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

    if (std::isprint(key)) {
      // Wait until the user inputs that key
      std::cout << '\'' << (char)key << "' with chord "
                << chord.to_string() << '\n';
      while (true) {
        const char obs = std::cin.get();
        if (obs == key) {
          break;
        }
      }
    } else {
      std::cout << "(skipping unprintable " << key
                << " with chord " << chord.to_string() << ")\n";
    }
  }

  return 0;
}
