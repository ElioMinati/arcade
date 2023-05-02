/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** ScoreSaver
*/

#include <vector>
#include <sstream>
#include "ScoreSaver.hpp"
#include "FileUtils.hpp"

void Arcade::ScoreSaver::addToMultimap(std::string user, std::string game, int score)
{
    if (globalScores.find(user) != globalScores.end()) {
        globalScores[user][game] = score;
    } else {
        globalScores[user] = {{game, score}};
    }
}

Arcade::ScoreSaver::ScoreSaver()
{
    if (!FileUtils::FileExists(scoreSavingPath))
        return;
    std::string fileContent = FileUtils::readFromFile(scoreSavingPath);
    std::vector<std::string> fileLines;

    if (fileContent.find('\n') == std::string::npos) {
        fileLines.push_back(fileContent);
    } else {
        while (fileContent.find('\n') != std::string::npos) {
            fileLines.push_back(fileContent.substr(0, fileContent.find('\n')));
            fileContent.erase(0, fileContent.find('\n') + 1);
        }
    }

    for (const auto &line: fileLines) {
        std::stringstream ss(line);
        std::string user;
        std::string game;
        int highScore;
        ss >> user;
        user.erase(user.begin());
        user.erase(user.end() - 1);
        ss >> game;
        ss >> highScore;
        this->addToMultimap(user, game, highScore);
    }
}

void Arcade::ScoreSaver::saveToFile()
{
    std::ofstream toSaveIn(scoreSavingPath);

    for (const auto &user: globalScores) {
        for (const auto &game: user.second) {
            toSaveIn << "\"" << user.first << "\" " << game.first << " " << game.second << "\n";
        }
    }
    toSaveIn.close();
}

void Arcade::ScoreSaver::SaveScore(std::string user, std::string game, int score)
{
    if ((globalScores.find(user) != globalScores.end()) && (globalScores[user].find(game) != globalScores[user].end())) {
        if (globalScores[user][game] < score) {
            globalScores[user][game] = score;
        }
    } else if ((globalScores.find(user) == globalScores.end())) {
        globalScores[user] = {{game, score}};
    } else {
        globalScores[user][game] = score;
    }
    this->saveToFile();
}

int Arcade::ScoreSaver::getHighScore(std::string user, std::string game)
{
    if ((globalScores.find(user) != globalScores.end()) && (globalScores[user].find(game) != globalScores[user].end())) {
        return globalScores[user][game];
    }
    return 0;
}
