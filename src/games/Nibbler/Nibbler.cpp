/*
** EPITECH PROJECT, 2022
** teck_2
** File description:
** test.c
*/

#include <chrono>
#include "Nibbler.hpp"
#include "MapMessages.hpp"

extern "C" Arcade::IGameLib *entryPoint()
{
    return new Arcade::Nibbler();
}

Arcade::Nibbler::Nibbler()
{
}

void Arcade::Nibbler::goodmap()
{
	int rows = Nibbler_map.size();
    int cols = Nibbler_map[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
			if (Nibbler_map[i][j] == 'm')
				Nibbler_map[i][j] = '1';
		}
	}
}

void Arcade::Nibbler::setMap(std::vector<std::string> map)
{
    Nibbler_map = map;
}

std::string Arcade::Nibbler::getGameMusic()
{
    return backgroundMusic;
}

std::string Arcade::Nibbler::getInLoopMusic()
{
	return musicInLoop;
}

void Arcade::Nibbler::applyAction(Arcade::Actions action)
{
	int tmp_x = moove_x;
	int tmp_y = moove_y;
	if (action == MOVE_LEFT && last_action != MOVE_RIGHT) {
		spriteDisplayMap['5'] = "assets/snake-head-left.png";
		moove_x = 0;
		moove_y = -1;
		stop = 0;
		if (Nibbler_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_LEFT;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
		}
	}
	if (action == MOVE_RIGHT && last_action != MOVE_LEFT) {
		spriteDisplayMap['5'] = "assets/snake-head-right.png";
		moove_x = 0;
		moove_y = 1;
		stop = 0;
		if (Nibbler_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_RIGHT;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
		}
	}
	if (action == MOVE_UP && last_action != MOVE_DOWN) {
		spriteDisplayMap['5'] = "assets/snake-head-up.png";
		moove_x = -1;
		moove_y = 0;
		stop = 0;
		if (Nibbler_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_UP;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
		}
	}
	if (action == MOVE_DOWN && last_action != MOVE_UP) {
		spriteDisplayMap['5'] = "assets/snake-head-down.png";
		moove_x = 1;
		moove_y = 0;
		stop = 0;
		if (Nibbler_map[start_x + moove_x][start_y + moove_y] != '1')
			last_action = MOVE_DOWN;
		else {
			moove_x = tmp_x;
			moove_y = tmp_y;
		}
	}
}

void Arcade::Nibbler::start()
{
	Nibbler_map[last_x][last_y] = '.';
	spriteDisplayMap = customSpriteMap;
}

int Arcade::Nibbler::getScore()
{
	return score;
}

void Arcade::Nibbler::sendInput(Arcade::Keys key)
{
	if (actionMap.find(key) != actionMap.end())
		this->applyAction(actionMap[key]);
}

std::vector<std::string> Arcade::Nibbler::getGrid()
{
	if (loose) {
		return Arcade::gameOverMessage;
	}
	if (stop == 0) {
		int moove = 0;
		int tmp_x = start_x;
		int tmp_y = start_y;
		if (Nibbler_map[start_x + moove_x][start_y + moove_y] == '1') {
			loose = 1;
			musicInLoop = "";
		}
		else if (Nibbler_map[start_x + moove_x][start_y + moove_y] == 'X') {
			moove = 1;
			int inter = 0;
			if (Nibbler_map[start_x][start_y - 1] == '.' || Nibbler_map[start_x][start_y - 1] == '2') {
				last_action = MOVE_LEFT;
				moove_x = 0;
				moove_y = -1;
				inter++;
			} 
			if (Nibbler_map[start_x][start_y + 1] == '.' || Nibbler_map[start_x][start_y + 1] == '2') {
				last_action = MOVE_RIGHT;
				moove_x = 0;
				moove_y = 1;
				inter++;
			}
			if (Nibbler_map[start_x + 1][start_y] == '.' || Nibbler_map[start_x + 1][start_y] == '2') {
				last_action = MOVE_DOWN;
				moove_x = 1;
				moove_y = 0;
				inter++;
			}
			if (Nibbler_map[start_x - 1][start_y] == '.' || Nibbler_map[start_x - 1][start_y] == '2') {
				last_action = MOVE_UP;
				moove_x = -1;
				moove_y = 0;
				inter++;
			}
			if (inter == 2) {
				last_action = NONE;
				stop = 1;
			}
			musicInLoop = "";
		} else if (Nibbler_map[start_x + moove_x][start_y + moove_y] == '2') {
			Nibbler_map[start_x][start_y] = '1';
			Nibbler_map[start_x + moove_x][start_y + moove_y] = '5';
			start_y = start_y + moove_y;
			start_x = start_x + moove_x;
			score += 10;
			neweat();
			moove = 1;
			musicInLoop = inLoopMusic;
		} else {
			Nibbler_map[start_x][start_y] = '1';
			Nibbler_map[start_x + moove_x][start_y + moove_y] = '5';
			Nibbler_map[start_x][start_y] = 'm';
			Nibbler_map[last_x][last_y] = '.';
			start_y = start_y + moove_y;
			start_x = start_x + moove_x;
			musicInLoop = "";
		}
		while (moove != 1) {
			if (Nibbler_map[tmp_x - 1][tmp_y] == '1') {
				Nibbler_map[tmp_x - 1][tmp_y] = 'm';
				tmp_x = tmp_x - 1;
			} else if (Nibbler_map[tmp_x][tmp_y - 1] == '1') {
				Nibbler_map[tmp_x][tmp_y - 1] = 'm';
				tmp_y = tmp_y - 1;
			} else if (Nibbler_map[tmp_x + 1][tmp_y] == '1') {
				Nibbler_map[tmp_x + 1][tmp_y] = 'm';
				tmp_x = tmp_x + 1;
			} else if (Nibbler_map[tmp_x][tmp_y + 1] == '1') {
				Nibbler_map[tmp_x][tmp_y + 1] = 'm';
				tmp_y = tmp_y + 1;
			} else {
				last_x = tmp_x;
				last_y = tmp_y;
				moove = 1;
			}
		}
		this->goodmap();
	}
	return Nibbler_map;
}

std::unordered_map<char, Arcade::Colors> Arcade::Nibbler::getColorMap()
{
    return colorMap;
}

std::unordered_map<char, char> Arcade::Nibbler::getCharDisplayMap()
{
    return charDisplayMap;
}

std::unordered_map<char, std::string> Arcade::Nibbler::getSpritesMap()
{
    return spriteDisplayMap;
}

void Arcade::Nibbler::neweat()
{
	while (1) {
		int rand_y = 1 + std::rand() % 16;
		int rand_x = 1 + std::rand() % 17;
		if (Nibbler_map[rand_x][rand_y] == '.') {
			Nibbler_map[rand_x][rand_y] = '2';
			break;
		}
	}
}