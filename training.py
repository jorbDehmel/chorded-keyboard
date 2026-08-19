"""
This is a script you can run to learn how to use the keyboard
"""

import random
import curses
from generate_arduino_sketch import default_setup, \
    ChordedKeyboardSchema


def curses_key_to_str(curses_key) -> str:
    """
    Converts a key as received from curses' getch() into its
    corresponding arduino keyboard.h string.
    """
    if curses_key == '\t':
        return 'KEY_TAB'
    if curses_key == '\n':
        return 'KEY_RETURN'
    if curses_key in ['KEY_LEFT', 'KEY_UP', 'KEY_RIGHT',
                      'KEY_DOWN']:
        return f'{curses_key}_ARROW'
    if curses_key == '^[':
        return 'KEY_ESC'
    return curses_key


def main_loop(scr, schema: ChordedKeyboardSchema) -> None:
    """
    Main training loop
    """
    total: int = 0
    correct: int = 0
    while True:
        chord = random.choice(list(schema.schema.keys()))
        exp_key = schema.schema[chord]
        if len(exp_key) > 1 and not exp_key.startswith('KEY_'):
            continue
        scr.clear()
        scr.addstr(0, 0, f'Value: {exp_key}')
        p = 0 if total == 0 else 100 * correct / total
        scr.addstr(3, 0, f'Accuracy: {round(p)}%')
        scr.addstr(4, 0, '(ctrl+C to quit)')
        scr.refresh()

        i: int = 0
        while True:
            if i == 1:
                scr.addstr(1, 0, f'Hint: {chord}')
                scr.refresh()
            elif i >= 5:
                break

            ch = scr.getkey()
            obs_key = curses_key_to_str(ch)
            if obs_key == exp_key:
                break

            scr.addstr(
                2, 0,
                f'Expected {exp_key}, saw {obs_key}'
            )
            scr.refresh()
            i += 1

        total += 1
        if i == 0:
            correct += 1


if __name__ == '__main__':
    curses.wrapper(main_loop, default_setup)
