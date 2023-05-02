/*
** EPITECH PROJECT, 2022
** teck_2
** File description:
** Ncurse.hpp
*/

#ifndef _NCURSE_HPP_
#define _NCURSE_HPP_

#include <vector>
#include <ios>
#include <iostream>
#include <ncurses.h>
#include "IGraphicLib.hpp"
#include "Keys.hpp"
#include "Graphics.hpp"

static std::unordered_map<Arcade::Colors, std::pair<int, int>> colorPairs {
    {Arcade::ARC_COLOR_BLACK, std::make_pair(0, COLOR_BLACK)},
    {Arcade::ARC_COLOR_RED, std::make_pair(1, COLOR_RED)},
    {Arcade::ARC_COLOR_GREEN, std::make_pair(2, COLOR_GREEN)},
    {Arcade::ARC_COLOR_YELLOW, std::make_pair(3, COLOR_YELLOW)},
    {Arcade::ARC_COLOR_BLUE, std::make_pair(4, COLOR_BLUE)},
    {Arcade::ARC_COLOR_MAGENTA, std::make_pair(5, COLOR_MAGENTA)},
    {Arcade::ARC_COLOR_CYAN, std::make_pair(6, COLOR_CYAN)},
    {Arcade::ARC_COLOR_WHITE, std::make_pair(7, COLOR_WHITE)},

};

namespace Arcade {
    class Ncurses : public IGraphicLib {
        public:
            Ncurses();
            virtual ~Ncurses();
            virtual void start() override;
            virtual void displayGrid(std::vector<std::string>) override;
            virtual Arcade::Keys getUserInput() override;
            virtual void setGraphicMaps(std::unordered_map<char, Arcade::Colors>, std::unordered_map<char, char>) override;
            virtual void displayScore(int, std::vector<std::string>) override;
            virtual void setSpritesMap(std::unordered_map<char, std::string>) override;
            virtual std::size_t playSound(std::string) override;
            virtual void stopSound(std::size_t) override;
            virtual void displayHighScore(int score, std::vector<std::string> grid) override;

        private:
            std::unordered_map<char, Arcade::Colors> _colorMap = {};
            std::unordered_map<char, char> _charDisplayMap = {};
            SCREEN *_screen;
    };
};

#endif