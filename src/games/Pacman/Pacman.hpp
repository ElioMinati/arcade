/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
    #define PACMAN_HPP_
    #include <iostream>
    #include <thread>
    #include <unordered_map>
    #include <vector>
    #include "IGameLib.hpp"
    #include "Graphics.hpp"
    #include "Ghost.hpp"

// static std::vector<std::string> map = {
// 	"XXXXXXXXXXXXXXXXXXX",
// 	"X........X........X",
// 	"XPXX.XXX.X.XXX.XXPX",
// 	"X.................X",
// 	"X.XX.X.XXXXX.X.XX.X",
// 	"X....X...X...X....X",
// 	"XXXX.XXX.X.XXX.XXXX",
// 	"...X.X.......X.X...",
// 	"...X.X.XX.XX.X.X...",
// 	"...X...X...X...X...",
// 	"...X.X.XX.XX.X.X...",
// 	"...X.X.......X.X...",
// 	"XXXX.X.XXXXX.X.XXXX",
//     "X........X........X",
//     "X.XX.XXX.X.XXX.XX.X",
//     "XP.X.....1.....X.PX",
//     "XX.X.X.XXXXX.X.X.XX",
//     "X....X...X...X....X",
//     "X.XXXXXX.X.XXXXXX.X",
//     "X.................X",
// 	"XXXXXXXXXXXXXXXXXXX"
// };

const static std::unordered_map<char, Arcade::Colors> colorMap = {
    {'X', Arcade::ARC_COLOR_BLUE},
    {'1', Arcade::ARC_COLOR_YELLOW},
    {'o', Arcade::ARC_COLOR_WHITE},
    {'P', Arcade::ARC_COLOR_YELLOW},
    {'2', Arcade::ARC_COLOR_RED},
    {'3', Arcade::ARC_COLOR_CYAN},
    {'4', Arcade::ARC_COLOR_MAGENTA},
    {'5', Arcade::ARC_COLOR_GREEN},
    {'6', Arcade::ARC_COLOR_BLUE},
};

const static std::unordered_map<char, char> charDisplayMap = {
    {'o', '.'},
    {'P', 'o'},
    {'1', 'O'},
    {'2', 'W'},
    {'3', 'W'},
    {'4', 'W'},
    {'5', 'W'},
    {'6', 'M'},
    {'.', ' '}
};

static std::unordered_map<char, std::string> customSpriteMap = {
    {'1', "assets/pacman-right.png"},
    {'o', "assets/nom.png"},
    {'P', "assets/powerup-nom.png"},
    {'2', "assets/ghost-1.png"},
    {'3', "assets/ghost-2.png"},
    {'4', "assets/ghost-3.png"},
    {'5', "assets/ghost-4.png"},
    {'6', "assets/ghost-eat.png"},
};

static std::string gameMusic = "assets/skeler-conversations.ogg";

static std::string inLoopMusic = "assets/pac-awa.ogg";

namespace Arcade {
    class Pacman : public IGameLib {
        public:
            Pacman();
            virtual ~Pacman() = default;
            virtual void start() override;
            virtual int getScore() override;
            virtual std::unordered_map<char, Arcade::Colors> getColorMap() override;
            virtual std::unordered_map<char, char> getCharDisplayMap() override;
            virtual std::unordered_map<char, std::string> getSpritesMap() override;
            virtual void sendInput(Arcade::Keys key) override;
            virtual bool canPutNom(int, int);
            virtual std::string getGameMusic() override;
            virtual std::string getInLoopMusic() override;
            virtual void setMap(std::vector<std::string> map) override;
            std::vector<std::string> getGrid();
            void applyAction(Arcade::Actions);
            virtual bool canMove();
            virtual void updateCoords();
            virtual void resetNoms();
            virtual bool hasNoms();
            virtual void computeAction();
            virtual void moveGhosts();
            virtual bool hasCollidedWithGhost();

        private:
            std::unordered_map<char, std::unique_ptr<Arcade::Ghost>> _ghosts;
            std::vector<std::string> pacman_map;
            std::pair<int, int> coords = std::make_pair(9, 11);
            std::pair<int, int> lastCoords;
            Arcade::Actions _currentAction = NONE;
            int score = 0;
            bool _gameOver = false;
            std::unordered_map<char, std::string> spriteDisplayMap;
            std::string musicInLoop;
            int powerupCountdown = 0;
            int ghostFirstMoveCountdown = 20;
    };
}

extern "C" Arcade::IGameLib *entryPoint();

#endif /* !PACMAN_HPP_ */
