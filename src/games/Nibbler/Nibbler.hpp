/*
** EPITECH PROJECT, 2022
** teck_2
** File description:
** Nibbler.hpp
*/

#ifndef _NIBBLER_HPP_
#define _NIBBLER_HPP_

#include <vector>
#include <ios>
#include <iostream>
#include <tuple>
#include <cstring>
#include <thread>
#include "IGameLib.hpp"
#include "Keys.hpp"

// static std::vector<std::string> map = {
// 	"XXXXXXXXXXXXXXXXXXX",
// 	"X..2...2...2...2..X",
// 	"X.XXXXX.X2X.XXXXX.X",
// 	"X2...2..X.X..2...2X",
// 	"X.XXX.XXX.XXX.XXX.X",
// 	"X.X.X..2...2..X.X.X",
// 	"X.XXX.XXXXXXX.XXX.X",
// 	"X2..2.........2..2X",
// 	"XXX.XXXXX2XXXXX.XXX",
// 	"X...2.........2...X",
// 	"X.XXXXXXX.XXXXXXX.X",
// 	"X..2....X.X....2..X",
// 	"X.XXXXX.X.X.XXXXX.X",
//     "X.....X..2..X.....X",
//     "X2X.X2.2X.X2.2X.X2X",
//     "X2X.XXXXX.XXXXX.X2X",
//     "X......1111.......X",
// 	"XXXXXXXXXXXXXXXXXXX"
// };

const static std::unordered_map<char, Arcade::Colors> colorMap = {
    {'X', Arcade::ARC_COLOR_BLUE},
    {'1', Arcade::ARC_COLOR_GREEN},
    {'5', Arcade::ARC_COLOR_GREEN},
    {'2', Arcade::ARC_COLOR_RED}
};

const static std::unordered_map<char, char> charDisplayMap = {
    {'.', ' '},
    {'1', 'D'},
    {'5', 'D'},
    {'2', 'o'}
};

static std::unordered_map<char, std::string> customSpriteMap = {
    {'1', "assets/snake-body.png"},
    {'5', "assets/snake-head-right.png"},
    {'2', "assets/cherry.png"},
};

static const std::string inLoopMusic = "assets/nomnom-snake.ogg";

static const std::string backgroundMusic = "assets/know-skeler.ogg";

namespace Arcade {
    class Nibbler : public IGameLib {
        public:
            Nibbler();
            virtual ~Nibbler() = default;
            virtual void start() override;
            virtual int getScore() override;
            virtual void sendInput(Arcade::Keys key) override;
            virtual std::unordered_map<char, Arcade::Colors> getColorMap() override;
            virtual std::unordered_map<char, char> getCharDisplayMap() override;
            virtual std::unordered_map<char, std::string> getSpritesMap() override;
            virtual std::string getGameMusic() override;
            virtual std::string getInLoopMusic() override;
            std::vector<std::string> getGrid();
            void applyAction(Arcade::Actions);
            void goodmap();
            void neweat();
            virtual void setMap(std::vector<std::string> map) override;

        private:
            std::vector<std::string> Nibbler_map;
            int last_x = 16;
            int last_y = 7;
            int start_x = 16;
            int start_y = 10;
            int score = 0;
            int moove_x = 0;
            int moove_y = 1;
            int loose = 0;
            int stop = 0;
            Arcade::Actions last_action = MOVE_RIGHT;
            std::unordered_map<char, std::string> spriteDisplayMap;
            std::string musicInLoop = "";
    };
}

extern "C" Arcade::IGameLib *entryPoint();

#endif