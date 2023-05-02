/*
** EPITECH PROJECT, 2022
** teck_2
** File description:
** test.c
*/

#include <chrono>
#include "Snake.hpp"
#include "MapMessages.hpp"

extern "C" Arcade::IGameLib *entryPoint()
{
    return new Arcade::Snake();
}

Arcade::Snake::Snake()
{
}

std::string Arcade::Snake::getGameMusic()
{
    return backgroundMusic;
}

std::string Arcade::Snake::getInLoopMusic()
{
	return musicInLoop;
}

void Arcade::Snake::goodmap()
{
	int rows = snake_map.size();
    int cols = snake_map[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
			if (snake_map[i][j] == 'm')
				snake_map[i][j] = '1';
		}
	}
}

void Arcade::Snake::applyAction(Arcade::Actions action)
{
	int tmp_x = moove_x;
	int tmp_y = moove_y;
	if (action == MOVE_LEFT && last_action != MOVE_RIGHT) {
		spriteDisplayMap['5'] = "assets/snake-head-left.png";
		moove_x = 0;
		moove_y = -1;
		if (snake_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_LEFT;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
			loose = 1;
		}
	}
	if (action == MOVE_RIGHT && last_action != MOVE_LEFT) {
		spriteDisplayMap['5'] = "assets/snake-head-right.png";
		moove_x = 0;
		moove_y = 1;
		if (snake_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_RIGHT;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
			loose = 1;
		}
	}
	if (action == MOVE_UP && last_action != MOVE_DOWN) {
		spriteDisplayMap['5'] = "assets/snake-head-up.png";
		moove_x = -1;
		moove_y = 0;
		if (snake_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_UP;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
			loose = 1;
		}
	}
	if (action == MOVE_DOWN && last_action != MOVE_UP) {
		spriteDisplayMap['5'] = "assets/snake-head-down.png";
		moove_x = 1;
		moove_y = 0;
		if (snake_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_DOWN;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
			loose = 1;
		}
	}
}

void Arcade::Snake::start()
{
	snake_map[last_x][last_y] = '.';
	spriteDisplayMap = customSpriteMap;
}

void Arcade::Snake::setMap(std::vector<std::string> map)
{
    snake_map = map;
}

int Arcade::Snake::getScore()
{
	return score;
}

void Arcade::Snake::sendInput(Arcade::Keys key)
{
	if (actionMap.find(key) != actionMap.end())
		this->applyAction(actionMap[key]);
}

std::vector<std::string> Arcade::Snake::getGrid()
{
	if (loose) {
		return Arcade::gameOverMessage;
	}
	int moove = 0;
	int tmp_x = start_x;
	int tmp_y = start_y;
	if (snake_map[start_x + moove_x][start_y + moove_y] == 'X') {
		loose = 1;
		moove = 1;
		musicInLoop = "";
		return Arcade::gameOverMessage;
	} else if (snake_map[start_x + moove_x][start_y + moove_y] == '1') {
		loose = 1;
		musicInLoop = "";
	} else if (snake_map[start_x + moove_x][start_y + moove_y] == '2') {
		snake_map[start_x][start_y] = '1';
		snake_map[start_x + moove_x][start_y + moove_y] = '5';
		start_y = start_y + moove_y;
		start_x = start_x + moove_x;
		score += 10;
		moove = 1;
		musicInLoop = inLoopMusic;
		neweat();
	} else {
		snake_map[start_x + moove_x][start_y + moove_y] = '5';
		snake_map[start_x][start_y] = 'm';
		snake_map[last_x][last_y] = '.';
		start_y = start_y + moove_y;
		start_x = start_x + moove_x;
		musicInLoop = "";
	}
	while (moove != 1) {
		if (snake_map[tmp_x - 1][tmp_y] == '1') {
			snake_map[tmp_x - 1][tmp_y] = 'm';
			tmp_x = tmp_x - 1;
		} else if (snake_map[tmp_x][tmp_y - 1] == '1') {
			snake_map[tmp_x][tmp_y - 1] = 'm';
			tmp_y = tmp_y - 1;
		} else if (snake_map[tmp_x + 1][tmp_y] == '1') {
			snake_map[tmp_x + 1][tmp_y] = 'm';
			tmp_x = tmp_x + 1;
		} else if (snake_map[tmp_x][tmp_y + 1] == '1') {
			snake_map[tmp_x][tmp_y + 1] = 'm';
			tmp_y = tmp_y + 1;
		} else {
			last_x = tmp_x;
			last_y = tmp_y;
			moove = 1;
		}
	}
	this->goodmap();
	return snake_map;
}

std::unordered_map<char, Arcade::Colors> Arcade::Snake::getColorMap()
{
    return colorMap;
}

std::unordered_map<char, char> Arcade::Snake::getCharDisplayMap()
{
    return charDisplayMap;
}

std::unordered_map<char, std::string> Arcade::Snake::getSpritesMap()
{
    return spriteDisplayMap;
}

void Arcade::Snake::neweat()
{
	while (1) {
		int rand_y = 1 + std::rand() % 31;
		int rand_x = 1 + std::rand() % 11;
		if (snake_map[rand_x][rand_y] == '.') {
			snake_map[rand_x][rand_y] = '2';
			break;
		}
	}
}
