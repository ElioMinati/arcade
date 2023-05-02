/*
** EPITECH PROJECT, 2022
** teck_2
** File description:
** Ncurse.cpp
*/

#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <thread>
#include "Sfml.hpp"
#include "MapMessages.hpp"

extern "C" Arcade::IGraphicLib *entryPoint()
{
    return new Arcade::Sfml();
}

Arcade::Sfml::Sfml()
{
}

void Arcade::Sfml::setGraphicMaps(std::unordered_map<char, Arcade::Colors> colorMap, std::unordered_map<char, char> textureMap)
{
    _colorMap = colorMap;
    _charDisplayMap = textureMap;
}

Arcade::Keys Arcade::Sfml::getUserInput()
{
    sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                return Arcade::Keys::ESC;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up)
                    return Arcade::Keys::UP_ARROW;
                if (event.key.code == sf::Keyboard::Down)
                    return Arcade::Keys::DOWN_ARROW;
                if (event.key.code == sf::Keyboard::Left)
                    return Arcade::Keys::LEFT_ARROW;
                if (event.key.code == sf::Keyboard::Right)
                    return Arcade::Keys::RIGHT_ARROW;
                if (event.key.code == sf::Keyboard::Escape)
                    return Arcade::Keys::ESC;
                if (event.key.code == sf::Keyboard::Enter)
                    return Arcade::Keys::ENTER;
                if (event.key.code == sf::Keyboard::G)
                    return Arcade::Keys::G;
                if (event.key.code == sf::Keyboard::V)
                    return Arcade::Keys::V;
                if (event.key.code == sf::Keyboard::R)
                    return Arcade::Keys::R;
                if (event.key.code == sf::Keyboard::M)
                    return Arcade::Keys::M;
                break;
            default:
                break;
        }
    }
    return Arcade::Keys::NO;
}

void Arcade::Sfml::displayGrid(std::vector<std::string> map)
{
    window.clear();
    if (map == Arcade::gameOverMessage) {
        gameOverSprite.setOrigin(gameOverTexture.getSize().x / 2, gameOverTexture.getSize().y / 2);
        gameOverSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        window.draw(gameOverSprite);
    } else {
        for (std::size_t y = 0; y < map.size(); ++y) {
            for (std::size_t x = 0; x < map[y].size(); ++x) {
                if (rawSpritesMap.size() > 0 && userDefinedSprites.find(map[y][x]) != userDefinedSprites.end()) {
                    userDefinedSprites[map[y][x]].setPosition(x * displayGap, y * displayGap);
                    window.draw(userDefinedSprites[map[y][x]]);
                } else if (_colorMap.find(map[y][x]) != _colorMap.end()) {
                    customColorSprites[_colorMap[map[y][x]]].setPosition(x * displayGap, y * displayGap);
                    window.draw(customColorSprites[_colorMap[map[y][x]]]);
                } else {
                    customColorSprites[Arcade::Colors::ARC_COLOR_BLACK].setPosition(x * displayGap, y * displayGap);
                    window.draw(customColorSprites[Arcade::Colors::ARC_COLOR_BLACK]);
                }
            }
        }
    }
}

void Arcade::Sfml::displayScore(int score, std::vector<std::string> grid)
{
    scoreText.setString(std::string("score: ") + std::to_string(score));
    scoreText.setPosition((grid[0].size() * displayGap) + 50, static_cast<int>((grid.size() * displayGap) / 2));
    window.draw(scoreText);
}

void Arcade::Sfml::displayHighScore(int score, std::vector<std::string> grid)
{
    scoreText.setString(std::string("High score: ") + std::to_string(score));
    scoreText.setPosition((grid[0].size() * displayGap) + 50, static_cast<int>((grid.size() * displayGap) / 2 + 100));
    window.draw(scoreText);
    window.display();
}

void Arcade::Sfml::start()
{
    for (auto &color: colorPairs) {
        customColorImageMap[color.first].create(displayGap, displayGap, color.second);
        customColorTextureMap[color.first].loadFromImage(customColorImageMap[color.first]);
        customColorSprites[color.first] = sf::Sprite(customColorTextureMap[color.first]);
    }
    loadedFont.loadFromFile("assets/Russo_One.ttf");
    gameOverTexture.loadFromFile("assets/game-over.jpg");
    gameOverSprite = sf::Sprite(gameOverTexture);
    scoreText.setFont(loadedFont);
    scoreText.setFillColor(sf::Color(255, 255, 255));
    window.create(sf::VideoMode(1920, 1080), "Map");
    window.setFramerateLimit(60);
}

void Arcade::Sfml::setSpritesMap(std::unordered_map<char, std::string> spriteMap)
{
    rawSpritesMap.clear();
    userDefinedTextures.clear();
    rawSpritesMap = spriteMap;
    for (auto &rawSprite: rawSpritesMap) {
        userDefinedTextures[rawSprite.first].loadFromFile(rawSprite.second);
        userDefinedSprites[rawSprite.first] = sf::Sprite(userDefinedTextures[rawSprite.first]);
        userDefinedSprites[rawSprite.first].setScale(static_cast<float>(displayGap) / 64, static_cast<float>(displayGap) / 64);
    }
}

std::size_t Arcade::Sfml::playSound(std::string path)
{
    if (path.empty())
        return 0;
    if (soundBuffers.find(path) == soundBuffers.end()) {
        sf::SoundBuffer buf;

        soundBuffers[path] = buf;
        if (!soundBuffers[path].loadFromFile(path)) {
            soundBuffers.erase(path);
            return 0;
        }
    }
    currentMusicPlaying[usedMusicIndex] = sf::Sound(soundBuffers[path]);
    currentMusicPlaying[usedMusicIndex].play();
    usedMusicIndex++;
    return usedMusicIndex - 1;
    return 0;
}

void Arcade::Sfml::stopSound(std::size_t index) {
    if (currentMusicPlaying.find(index) != currentMusicPlaying.end()) {
        currentMusicPlaying[index].stop();
        currentMusicPlaying.erase(index);
    }
}

Arcade::Sfml::~Sfml()
{
    for (auto &sound: currentMusicPlaying) {
        sound.second.stop();
    }
    rawSpritesMap.clear();
    userDefinedTextures.clear();
    currentMusicPlaying.clear();
	soundBuffers.clear();
    window.close();
}
