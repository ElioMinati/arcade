/*
** EPITECH PROJECT, 2022
** teck_2
** File description:
** Snake.hpp
*/

#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <vector>
#include <ios>
#include <iostream>
#include <tuple>
#include <cstring>
#include <thread>
#include "IGameLib.hpp"
#include "Keys.hpp"

// static std::vector<std::string> map = {
// 	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
// 	"X................................X",
// 	"X................................X",
// 	"X................................X",
// 	"X................2...............X",
// 	"X................................X",
// 	"X................................X",
// 	"X..............1111..............X",
// 	"X................................X",
// 	"X................................X",
// 	"X................................X",
// 	"X................................X",
// 	"X................................X",
// 	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
// };

static std::unordered_map<char, Arcade::Colors> colorMap = {
    {'X', Arcade::ARC_COLOR_BLUE},
    {'1', Arcade::ARC_COLOR_GREEN},
    {'5', Arcade::ARC_COLOR_GREEN},
    {'2', Arcade::ARC_COLOR_RED}
};

static std::unordered_map<char, char> charDisplayMap = {
    {'.', ' '},
    {'1', 'D'},
    {'5', 'D'},
    {'2', 'o'}
};

static std::unordered_map<char, std::string> customSpriteMap = {
    {'1', "assets/snake-body.png"},
    {'5', "assets/snake-head-left.png"},
    {'2', "assets/cherry.png"},
};

static const std::string inLoopMusic = "assets/nomnom-snake.ogg";

static const std::string backgroundMusic = "assets/exodus-skeler.ogg";

namespace Arcade {
    class Snake : public IGameLib {
        public:
            Snake();
            virtual ~Snake() = default;
            virtual void start() override;
            virtual int getScore() override;
            virtual void sendInput(Arcade::Keys key) override;
            virtual std::unordered_map<char, Arcade::Colors> getColorMap() override;
            virtual std::unordered_map<char, char> getCharDisplayMap() override;
            virtual std::unordered_map<char, std::string> getSpritesMap() override;
            virtual std::string getGameMusic() override;
            virtual std::string getInLoopMusic() override;
            virtual void setMap(std::vector<std::string> map) override;
            std::vector<std::string> getGrid();
            void applyAction(Arcade::Actions);
            void goodmap();
            void neweat();
        private:
            std::vector<std::string> snake_map;
            int last_x = 7;
            int last_y = 18;
            int start_x = 7;
            int start_y = 15;
            int score = 0;
            int moove_x = 0;
            int moove_y = -1;
            int loose = 0;
            Arcade::Actions last_action = MOVE_RIGHT;
            std::unordered_map<char, std::string> spriteDisplayMap;
            std::string musicInLoop = "";
    };
}

extern "C" Arcade::IGameLib *entryPoint();

#endif