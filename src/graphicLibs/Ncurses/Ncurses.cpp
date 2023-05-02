/*
** EPITECH PROJECT, 2022
** teck_2
** File description:
** Ncurse.cpp
*/

#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include "Ncurses.hpp"

extern "C" Arcade::IGraphicLib *entryPoint()
{
    return new Arcade::Ncurses();
}

Arcade::Ncurses::Ncurses()
{
}

void Arcade::Ncurses::setGraphicMaps(std::unordered_map<char, Arcade::Colors> colorMap, std::unordered_map<char, char> charDisplayMap)
{
    _colorMap = colorMap;
    _charDisplayMap = charDisplayMap;
}

Arcade::Keys Arcade::Ncurses::getUserInput()
{
    int ch = getch();
    if (ch == KEY_LEFT)
        return Arcade::Keys::LEFT_ARROW;
    if (ch == KEY_RIGHT)
        return Arcade::Keys::RIGHT_ARROW;
    if (ch == KEY_UP)
        return Arcade::Keys::UP_ARROW;
    if (ch == KEY_DOWN)
        return Arcade::Keys::DOWN_ARROW;
    if (ch == '\n')
        return Arcade::Keys::ENTER;
    if (ch == 27)
        return Arcade::Keys::ESC;
    if (ch == 'm')
        return Arcade::Keys::M;
    if (ch == 'g')
        return Arcade::Keys::G;
    if (ch == 'v')
        return Arcade::Keys::V;
    if (ch == 'r')
        return Arcade::Keys::R;
    return Arcade::Keys::NO;
}

void Arcade::Ncurses::displayGrid(std::vector<std::string> map)
{
    clear();
    refresh();
    int rows = map.size();
    int cols = map[0].size();
    if (LINES < rows || COLS < cols) {
        clear();
        mvprintw(0, static_cast<int>(COLS / 2), "%s", "The window is too small to display the game");
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((_colorMap.find(map[i][j]) != _colorMap.end()) && (colorPairs.find(_colorMap[map[i][j]]) != colorPairs.end()))
                attron(COLOR_PAIR(colorPairs[_colorMap[map[i][j]]].first));
            if (_charDisplayMap.find(map[i][j]) != _charDisplayMap.end())
                mvprintw(i, j, "%c", _charDisplayMap[map[i][j]]);
            else
                mvprintw(i, j, "%c", map[i][j]);
            if ((_colorMap.find(map[i][j]) != _colorMap.end()) && (colorPairs.find(_colorMap[map[i][j]]) != colorPairs.end()))
                attroff(COLOR_PAIR(colorPairs[_colorMap[map[i][j]]].first));
        }
    }
}

void Arcade::Ncurses::displayScore(int score, std::vector<std::string> grid)
{
    std::stringstream s;

    s << score;
    if (LINES < static_cast<int>(grid.size()) || COLS < static_cast<int>(grid[0].size()))
        return;
    mvprintw(static_cast<int>(grid.size() / 2) - 3, grid[0].size() + 1, "#############################");
    mvprintw(static_cast<int>(grid.size() / 2) - 2, grid[0].size() + 1, "#                           #");
    mvprintw(static_cast<int>(grid.size() / 2) - 1, grid[0].size() + 1, "# Score:                    #");
    mvprintw(static_cast<int>(grid.size() / 2) - 1, grid[0].size() + 10, s.str().c_str());
    mvprintw(static_cast<int>(grid.size() / 2), grid[0].size() + 1, "#                           #");
    mvprintw(static_cast<int>(grid.size() / 2) + 1, grid[0].size() + 1, "#                           #");
    mvprintw(static_cast<int>(grid.size() / 2) + 2, grid[0].size() + 1, "#############################");
}

void Arcade::Ncurses::displayHighScore(int score, std::vector<std::string> grid)
{
    std::stringstream s;

    s << score;
    if (LINES < static_cast<int>(grid.size()) || COLS < static_cast<int>(grid[0].size()))
        return;
    mvprintw(static_cast<int>(grid.size() / 2), grid[0].size() + 2, " High Score:");
    mvprintw(static_cast<int>(grid.size() / 2), grid[0].size() + 15, s.str().c_str());
}

void Arcade::Ncurses::start()
{
    _screen = newterm(getenv("TERM"), stdout, stdin);
    noecho_sp(_screen);
    timeout(50);
    keypad(stdscr, TRUE);
    curs_set_sp(_screen, 0);
    start_color_sp(_screen);
    for (const auto &color: colorPairs) {
        init_pair_sp(_screen, color.second.first, color.second.second, COLOR_BLACK);
    }
}

void Arcade::Ncurses::setSpritesMap(std::unordered_map<char, std::string> gMap)
{
    static_cast<void>(gMap);
}

std::size_t Arcade::Ncurses::playSound(std::string path)
{
    static_cast<void>(path);
    beep_sp(_screen);
    return 0;
}

void Arcade::Ncurses::stopSound(std::size_t index)
{
    static_cast<void>(index);
}

Arcade::Ncurses::~Ncurses()
{
    refresh();
    clear();
    endwin_sp(_screen);
}