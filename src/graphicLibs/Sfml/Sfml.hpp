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
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "IGraphicLib.hpp"
#include "Keys.hpp"
#include "Graphics.hpp"

static std::unordered_map<Arcade::Colors, sf::Color> colorPairs = {
    {Arcade::ARC_COLOR_RED, sf::Color(255, 0, 0)},
    {Arcade::ARC_COLOR_BLACK, sf::Color(0, 0, 0)},
    {Arcade::ARC_COLOR_GREEN, sf::Color(0, 255, 0)},
    {Arcade::ARC_COLOR_YELLOW, sf::Color(255, 255, 0)},
    {Arcade::ARC_COLOR_WHITE, sf::Color(255, 255, 255)},
    {Arcade::ARC_COLOR_BLUE, sf::Color(0, 0, 255)},
    {Arcade::ARC_COLOR_MAGENTA, sf::Color(255, 0, 255)},
    {Arcade::ARC_COLOR_CYAN, sf::Color(0, 255, 255)},
};

namespace Arcade {
    class Sfml : public IGraphicLib {
        public:
            Sfml();
            virtual ~Sfml();
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
            std::unordered_map<Arcade::Colors, sf::Texture> customColorTextureMap;
            std::unordered_map<Arcade::Colors, sf::Image> customColorImageMap;
            std::unordered_map<Arcade::Colors, sf::Sprite> customColorSprites;
            std::unordered_map<char, std::string> rawSpritesMap;
            std::unordered_map<char, sf::Texture> userDefinedTextures;
            std::unordered_map<char, sf::Sprite> userDefinedSprites;
            std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
            std::unordered_map<std::size_t, sf::Sound> currentMusicPlaying;
            std::size_t usedMusicIndex = 1;
            sf::RenderWindow window {};
            sf::Font loadedFont;
            sf::Text scoreText;
            sf::Texture gameOverTexture;
            sf::Sprite gameOverSprite;
            int displayGap = 30;
    };
};

#endif