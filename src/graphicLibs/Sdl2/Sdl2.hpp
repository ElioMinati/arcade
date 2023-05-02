/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Sdl2
*/

#ifndef SDL2_HPP
#define SDL2_HPP

#include <vector>
#include <ios>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "IGraphicLib.hpp"
#include "Keys.hpp"
#include "Graphics.hpp"

static std::unordered_map<Arcade::Colors, SDL_Color> colorPairs = {
    {Arcade::ARC_COLOR_RED, SDL_Color{255, 0, 0, 25}},
    {Arcade::ARC_COLOR_BLACK, SDL_Color{0, 0, 0, 25}},
    {Arcade::ARC_COLOR_GREEN, SDL_Color{0, 255, 0, 25}},
    {Arcade::ARC_COLOR_YELLOW, SDL_Color{255, 255, 0, 25}},
    {Arcade::ARC_COLOR_WHITE, SDL_Color{255, 255, 255, 25}},
    {Arcade::ARC_COLOR_BLUE, SDL_Color{0, 0, 255, 25}},
    {Arcade::ARC_COLOR_MAGENTA, SDL_Color{255, 0, 255, 25}},
    {Arcade::ARC_COLOR_CYAN, SDL_Color{0, 255, 255, 25}},
};

namespace Arcade {
    class Sdl2 : public IGraphicLib {
        public:
            Sdl2();
            virtual ~Sdl2();
            virtual void start() override;
            virtual void displayGrid(std::vector<std::string>) override;
            virtual Arcade::Keys getUserInput() override;
            virtual void setGraphicMaps(std::unordered_map<char, Arcade::Colors>, std::unordered_map<char, char>) override;
            virtual void setSpritesMap(std::unordered_map<char, std::string>) override;
            virtual void displayScore(int, std::vector<std::string>) override;
            virtual std::size_t playSound(std::string) override;
            virtual void stopSound(std::size_t) override;
            virtual void displayHighScore(int score, std::vector<std::string> grid) override;
        private:
            std::unordered_map<char, Arcade::Colors> _colorMap = {};
            std::unordered_map<char, char> _charDisplayMap = {};
            std::unordered_map<Arcade::Colors, SDL_Surface *> customColorImageMap {};
            std::unordered_map<Arcade::Colors, SDL_Texture *> customColorSprites {};

            SDL_Renderer *renderer;
            SDL_Window *window;
            int displayGap = 30;
            TTF_Font *font;
            std::unordered_map<char, std::string> rawSpritesMap {};
            std::unordered_map<char, SDL_Texture *> userDefinedSprites {};
            SDL_Texture *gameOver;
            // std::unordered_map<std::size_t, SDL_AudioDevice> currentMusicPlaying;
            // std::unordered_map<std::string, Uint8*> buf;
            // SDL_RWops* music;
            std::size_t usedMusicIndex = 1;
    };
};

#endif