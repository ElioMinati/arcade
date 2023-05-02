/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
    #define GHOST_HPP_
    #include <iostream>
    #include <vector>
    #include "Keys.hpp"

namespace Arcade
{
    class Ghost {
        public:
            Ghost(int, int);
            virtual ~Ghost() = default;
            virtual std::pair<int, int> getCoords();
            virtual void move(std::vector<std::string>);
            virtual void resetCoords(int x, int y);
            virtual bool wasEaten();
            virtual void resetStatus();

        private:
            std::pair<int, int> _coords;
            Arcade::Actions _currentDirection = NONE;
            bool _wasEaten = false;
    };
}


#endif /* !GHOST_HPP_ */
