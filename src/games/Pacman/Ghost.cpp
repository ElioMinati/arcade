/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Ghost
*/

#include "Ghost.hpp"

Arcade::Ghost::Ghost(int x, int y) : _coords(std::make_pair(x, y))
{
}

std::pair<int, int> Arcade::Ghost::getCoords()
{
    return _coords;
}

bool Arcade::Ghost::wasEaten()
{
    return _wasEaten;
}

void Arcade::Ghost::resetStatus()
{
    _wasEaten = false;
}

void Arcade::Ghost::resetCoords(int x, int y)
{
    _coords.first = x;
    _coords.second = y;
    _wasEaten = true;
}

void Arcade::Ghost::move(std::vector<std::string> map)
{
    std::vector<Arcade::Actions> availableDirections = {};

    if (map[_coords.second][_coords.first - 1] != 'X')
        availableDirections.push_back(Arcade::MOVE_LEFT);
    if (map[_coords.second][_coords.first + 1] != 'X')
        availableDirections.push_back(Arcade::MOVE_RIGHT);
    if (map[_coords.second - 1][_coords.first] != 'X')
        availableDirections.push_back(Arcade::MOVE_UP);
    if (map[_coords.second + 1][_coords.first] != 'X')
        availableDirections.push_back(Arcade::MOVE_DOWN);
    
    if (availableDirections.size() == 2 &&
    (std::abs(moveMap[availableDirections[0]].first) == std::abs(moveMap[availableDirections[1]].first))
    && (std::abs(moveMap[availableDirections[0]].second) == std::abs(moveMap[availableDirections[1]].second))
    && _currentDirection != NONE) {
        _coords.first += moveMap[_currentDirection].first;
        _coords.second += moveMap[_currentDirection].second;
        return;
    }
    _currentDirection = availableDirections[std::rand() % (availableDirections.size())];
    _coords.first += moveMap[_currentDirection].first;
    _coords.second += moveMap[_currentDirection].second;
}
