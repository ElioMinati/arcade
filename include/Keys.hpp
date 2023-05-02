/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Keys
*/

#ifndef KEYS_HPP_
    #define KEYS_HPP_
    #include <map>

namespace Arcade {
    enum Keys {
        LEFT_ARROW,
        RIGHT_ARROW,
        UP_ARROW,
        DOWN_ARROW,
        E = 'E',
        ESC,
        ENTER,
        G = 'G',
        V = 'V',
        R = 'R',
        M = 'M',
        NO
    };
    enum Actions {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        RESTART,
        QUIT,
        NONE,
    };
    static std::map<Keys, Actions> actionMap = {
        {LEFT_ARROW, MOVE_LEFT},
        {RIGHT_ARROW, MOVE_RIGHT},
        {DOWN_ARROW, MOVE_DOWN},
        {UP_ARROW, MOVE_UP},
        {E, RESTART},
        {ESC, QUIT}
    };
    static std::map<Actions, std::pair<int, int>> moveMap = {
        {MOVE_LEFT, std::make_pair(-1, 0)},
        {MOVE_RIGHT, std::make_pair(1, 0)},
        {MOVE_DOWN, std::make_pair(0, 1)},
        {MOVE_UP, std::make_pair(0, -1)},
    };
}

#endif /* !KEYS_HPP_ */
