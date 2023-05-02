/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Pacman
*/

#include <chrono>
#include "Pacman.hpp"
#include "MapMessages.hpp"

extern "C" Arcade::IGameLib *entryPoint()
{
    return new Arcade::Pacman();
}

Arcade::Pacman::Pacman()
{
}

std::string Arcade::Pacman::getGameMusic()
{
    return gameMusic;
}

std::string Arcade::Pacman::getInLoopMusic()
{
	return musicInLoop;
}

void Arcade::Pacman::start()
{
    _gameOver = false;
    spriteDisplayMap = customSpriteMap;
    this->resetNoms();
    _ghosts['2'] = std::make_unique<Arcade::Ghost>(8, 9);
    _ghosts['3'] = std::make_unique<Arcade::Ghost>(9, 9);
    _ghosts['4'] = std::make_unique<Arcade::Ghost>(10, 9);
    _ghosts['5'] = std::make_unique<Arcade::Ghost>(9, 8);
    musicInLoop = inLoopMusic;
}

void Arcade::Pacman::setMap(std::vector<std::string> map)
{
    pacman_map = map;
}

void Arcade::Pacman::applyAction(Arcade::Actions action)
{
    _currentAction = action;
}

bool Arcade::Pacman::canPutNom(int i, int j)
{
    if (i > 6 && i < 12 && (j < 3 || j > 15))
        return false;
    return true;
}

void Arcade::Pacman::resetNoms()
{
    for (std::size_t i = 0; i < pacman_map.size(); i++) {
        for (std::size_t j = 0; j < pacman_map[i].size(); j++) {
            if (this->canPutNom(i, j) && pacman_map[i][j] == '.')
                pacman_map[i][j] = 'o';
        }
    }
    pacman_map[2][1] = 'P';
    pacman_map[2][17] = 'P';
    pacman_map[15][1] = 'P';
    pacman_map[15][17] = 'P';
}

bool Arcade::Pacman::hasNoms()
{
    for (std::size_t i = 0; i < pacman_map.size(); i++) {
        for (std::size_t j = 0; j < pacman_map[i].size(); j++) {
            if (pacman_map[i][j] == 'o' || pacman_map[i][j] == 'P')
                return true;
        }
    }
    return false;
}

void Arcade::Pacman::sendInput(Arcade::Keys key)
{
	if (actionMap.find(key) != actionMap.end())
		this->applyAction(actionMap[key]);
}

bool Arcade::Pacman::canMove()
{
    if (moveMap.find(_currentAction) != moveMap.end()
        && (_currentAction == MOVE_LEFT || _currentAction == MOVE_RIGHT || _currentAction == MOVE_UP || _currentAction == MOVE_DOWN)) {
            char goTo = pacman_map[coords.second + moveMap[_currentAction].second][coords.first + moveMap[_currentAction].first];
        if (goTo == 'X')
            return false;
        return true;
    }
    return false;
}

void Arcade::Pacman::updateCoords()
{
    pacman_map[lastCoords.second][lastCoords.first] = '.';
    pacman_map[coords.second][coords.first] = '1';
}

std::unordered_map<char, Arcade::Colors> Arcade::Pacman::getColorMap()
{
    return colorMap;
}

std::unordered_map<char, char> Arcade::Pacman::getCharDisplayMap()
{
    return charDisplayMap;
}

std::unordered_map<char, std::string> Arcade::Pacman::getSpritesMap()
{
    return spriteDisplayMap;
}

void Arcade::Pacman::computeAction()
{
    powerupCountdown = (powerupCountdown > 0 ? (powerupCountdown - 1) : 0);
    ghostFirstMoveCountdown = (ghostFirstMoveCountdown > 0 ? (ghostFirstMoveCountdown - 1) : 0);
    if (pacman_map[coords.second][coords.first] == 'o') {
        score += 10;
        musicInLoop = inLoopMusic;
    } else if (pacman_map[coords.second][coords.first] == 'P') {
        powerupCountdown = 20;
        score += 20;
        musicInLoop = inLoopMusic;
        for (const auto &ghost: _ghosts) {
            ghost.second.get()->resetStatus();
        }
    } else {
        musicInLoop = "";
    }
    if (!this->hasNoms())
        this->resetNoms();
    if (_currentAction == MOVE_LEFT)
        this->spriteDisplayMap['1'] = "assets/pacman-left.png";
    if (_currentAction == MOVE_RIGHT)
        this->spriteDisplayMap['1'] = "assets/pacman-right.png";
    if (_currentAction == MOVE_UP)
        this->spriteDisplayMap['1'] = "assets/pacman-up.png";
    if (_currentAction == MOVE_DOWN)
        this->spriteDisplayMap['1'] = "assets/pacman-down.png";
}

void Arcade::Pacman::moveGhosts()
{
    for (const auto &ghost: _ghosts)
        ghost.second.get()->move(pacman_map);
}

bool Arcade::Pacman::hasCollidedWithGhost()
{
    for (const auto &ghost: _ghosts) {
        std::pair<int, int> ghostCoords = ghost.second.get()->getCoords();

        if ((coords.first == ghostCoords.first) && (coords.second == ghostCoords.second)) {
            if (powerupCountdown > 0 && ghost.second.get()->wasEaten()) {
                return true;
            } else if (powerupCountdown > 0)
                return false;
            return true;
        }
    }
    return false;
}

int Arcade::Pacman::getScore()
{
    return score;
}

std::vector<std::string> Arcade::Pacman::getGrid()
{
    if (ghostFirstMoveCountdown <= 0)
        this->moveGhosts();
    if (this->hasCollidedWithGhost()) {
        _gameOver = true;
    }
    if (_gameOver) {
        musicInLoop = "";
        return Arcade::gameOverMessage;
    }
    if (powerupCountdown > 0) {
        for (const auto &ghost: _ghosts) {
            std::pair<int, int> ghostCoords = ghost.second.get()->getCoords();

            if ((coords.first == ghostCoords.first) && (coords.second == ghostCoords.second)) {
                score += 200;
                ghost.second.get()->resetCoords(10, 9);
            }
        }
    }
    if (canMove()) {
        lastCoords.first = coords.first;
        lastCoords.second = coords.second;
        coords.first += moveMap[_currentAction].first;
        coords.second += moveMap[_currentAction].second;
        this->computeAction();
        this->updateCoords();
    } else {
        musicInLoop = "";
    }
    if (powerupCountdown > 0) {
        for (const auto &ghost: _ghosts) {
            std::pair<int, int> ghostCoords = ghost.second.get()->getCoords();

            if ((coords.first == ghostCoords.first) && (coords.second == ghostCoords.second)) {
                score += 200;
                ghost.second.get()->resetCoords(10, 9);
            }
        }
    }
    if (this->hasCollidedWithGhost()) {
        _gameOver = true;
    }
    if (_gameOver) {
        musicInLoop = "";
        return Arcade::gameOverMessage;
    }
    std::vector<std::string> mapWithGhosts = pacman_map;
    for (const auto &ghost: _ghosts) {
        std::pair<int, int> ghostCoords = ghost.second.get()->getCoords();
        if (powerupCountdown == 0 || ghost.second.get()->wasEaten()) {
            mapWithGhosts[ghostCoords.second][ghostCoords.first] = ghost.first;
        } else {
            mapWithGhosts[ghostCoords.second][ghostCoords.first] = '6';
        }
    }
	return mapWithGhosts;
}
