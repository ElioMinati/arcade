/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include <thread>
#include <chrono>
#include "InvalidFile.hpp"
#include "GameLaunchError.hpp"
#include "FileUtils.hpp"
#include "Core.hpp"

Arcade::Core::Core(std::string libPath)
{
    std::vector<std::string> allLibs = FileUtils::readDirectory("./lib/");

    this->parseLibs(allLibs);
    _currentGraphicStr = libPath;
    _currentGameStr = availableGameLibs[0];
    this->listGameLibraries();
    this->listGraphicLibraries();
    this->listenForUserName();
    if (this->setupMainMenu(libPath))
        return;
    this->start();
}

void Arcade::Core::parseLibs(std::vector<std::string> libs)
{
    for (const auto &lib: libs) {
        DLLoader gameLib(lib);
        DLLoader graphLib(lib);

        if (gameLib.getInstance<IGameLib>() != nullptr)
            availableGameLibs.push_back(lib);
        else if (graphLib.getInstance<IGraphicLib>() != nullptr)
            availableGraphicLibs.push_back(lib);
    }
}

std::vector<std::string> Arcade::Core::getMainMenuDisplay(bool displayGraphic, int &max_game, int &max_graphic)
{
    std::vector<std::string> menuDisplay = {
        "###############################################",
        "#    Games                ",
    };
    if (displayGraphic)
        menuDisplay[1].append("Graphic Libraries   #");
    else
        menuDisplay[1].append("                    #");
    for (const auto &game: availableGameLibs) {
        menuDisplay.push_back("#                                             #");
        std::string gameName = this->getLibnameFromPath(game);
        for (std::size_t i = 0; i < gameName.size(); i++)
            menuDisplay[menuDisplay.size() - 1][10 + i] = gameName[i];
        max_game++;
    }
    for (std::size_t i = 0; i < availableGraphicLibs.size() && displayGraphic; i++) {
        std::string graphName = this->getLibnameFromPath(availableGraphicLibs[i]);
        for (std::size_t j = 0; j < graphName.size(); j++)
            menuDisplay[2 + i][33 + j] = graphName[j];
        max_graphic++;
    }
    menuDisplay[2][8] = '>';
    if (displayGraphic)
        menuDisplay[2][31] = '>';
    menuDisplay.push_back("#                                             #");
    menuDisplay.push_back("###############################################");
    return menuDisplay;
}

bool Arcade::Core::setupMainMenu(std::string graphLibPath)
{
    bool inMenu = true;
    int min = 2;
    int max_game = 1;
    int max_graphic = 1;
    int currentGameIndex = 0;
    int currentGraphicIndex = 0;
    bool kill = false;
    bool gameSwitch = true;

    this->setGraphics("./lib/arcade_ncurses.so");
    std::vector<std::string> menuDisplay = this->getMainMenuDisplay(graphLibPath.empty(), max_game, max_graphic);
    _graphicLibInstance->setGraphicMaps({}, {});
    _graphicLibInstance->start();
    while (inMenu) {
        _graphicLibInstance->displayGrid(menuDisplay);
        Arcade::Keys userInput = _graphicLibInstance->getUserInput();
        if (userInput == Arcade::Keys::ESC)
            kill = true;
        if (userInput == Arcade::Keys::ESC || userInput == Arcade::Keys::ENTER)
            break;
        if (userInput == Arcade::Keys::DOWN_ARROW) {
            if (gameSwitch) {
                menuDisplay[min + currentGameIndex][8] = ' ';
                currentGameIndex += ((currentGameIndex + 1) > (max_game - min) ? 0 : 1 );
                menuDisplay[min + currentGameIndex][8] = '>';
            } else {
                menuDisplay[min + currentGraphicIndex][31] = ' ';
                currentGraphicIndex += ((currentGraphicIndex + 1) > (max_graphic - min) ? 0 : 1 );
                menuDisplay[min + currentGraphicIndex][31] = '>';
            }
        }
        if (userInput == Arcade::Keys::UP_ARROW) {
            if (gameSwitch) {
                menuDisplay[min + currentGameIndex][8] = ' ';
                currentGameIndex -= ((currentGameIndex - 1) < 0 ? 0 : 1 );
                menuDisplay[min + currentGameIndex][8] = '>';
            } else {
                menuDisplay[min + currentGraphicIndex][31] = ' ';
                currentGraphicIndex -= ((currentGraphicIndex - 1) < 0 ? 0 : 1 );
                menuDisplay[min + currentGraphicIndex][31] = '>';
            }
        }
        if (userInput == Arcade::Keys::LEFT_ARROW)
            gameSwitch = true;
        if (userInput == Arcade::Keys::RIGHT_ARROW && graphLibPath.empty())
            gameSwitch = false;
    }
    if (!graphLibPath.empty())
        this->setGraphics(graphLibPath);
    else
        this->setGraphics(availableGraphicLibs[currentGraphicIndex]);
    this->setGame(availableGameLibs[currentGameIndex]);
    return kill;
}

std::string Arcade::Core::getLibnameFromPath(std::string libPath)
{
    std::vector<std::string> decomposedPath = {};

    decomposedPath.push_back(libPath.substr(0, libPath.find("_")));
    libPath.erase(0, libPath.find("_") + 1);
    decomposedPath.push_back(libPath.substr(0, libPath.find(".")));
    if (decomposedPath.size() == 2)
        return decomposedPath[1];
    return "";
}

void Arcade::Core::listGameLibraries()
{
    std::cout << "Available Games:" << std::endl;
    for (auto &game: availableGameLibs)
        std::cout << "\t" << std::string(game) << std::endl;
}

void Arcade::Core::listGraphicLibraries()
{
    std::cout << "Available Graphic Libraries:" << std::endl;
    for (auto &lib: availableGraphicLibs) {
        std::cout << "\t" << std::string(lib) << std::endl;
    }
}

void Arcade::Core::listenForUserName()
{
    std::string username;
    std::cout << "Please enter your username:\n";
    std::getline(std::cin, _userName);
    if (_userName.find('\"') != std::string::npos || _userName.find(' ') != std::string::npos)
        throw Arcade::GameLaunchError("ERROR Arcave: Invalid name, please do not use '\"' or ' '");
}

void Arcade::Core::setGraphics(std::string libPath)
{
    _graphicLibInstance.reset();
    _graphicLibHandle.reset();
    _graphicLibHandle = std::make_unique<DLLoader>(libPath);
    _graphicLibInstance = std::unique_ptr<IGraphicLib>(_graphicLibHandle.get()->getInstance<IGraphicLib>());
    _loadedGraphics = true;
    _currentGraphicStr = libPath;
}

void Arcade::Core::setGame(std::string gamePath)    
{
    _gameLibInstance.reset();
    _gameLibHandle.reset();
    _gameLibHandle = std::make_unique<DLLoader>(gamePath);
    _gameLibInstance = std::unique_ptr<IGameLib>(_gameLibHandle->getInstance<IGameLib>());
    _gameLibInstance->setMap(FileUtils::readFromFileToVector(std::string("map/") + this->getLibnameFromPath(gamePath) + std::string(".txt")));
    _loadedGame = true;
    _currentGameStr = gamePath;
}

std::string Arcade::Core::getNextGameLib()
{
    for (std::size_t i = 0; i < availableGameLibs.size(); i++) {
        if (_currentGameStr == availableGameLibs[i] && (i + 1) < availableGameLibs.size())
            return availableGameLibs[i + 1];
        if (_currentGameStr == availableGameLibs[i])
            return availableGameLibs[0];
    }
    return availableGameLibs[0];
}

std::string Arcade::Core::getNextGraphicLib()
{
    for (std::size_t i = 0; i < availableGraphicLibs.size(); i++) {
        if (_currentGraphicStr == availableGraphicLibs[i] && (i + 1) < availableGraphicLibs.size())
            return availableGraphicLibs[i + 1];
        if (_currentGraphicStr == availableGraphicLibs[i])
            return availableGraphicLibs[0];
    }
    return availableGraphicLibs[0];
}

bool Arcade::Core::manageInputs(Arcade::Keys userInput, std::size_t &mainMusicId)
{
    if (userInput == Arcade::Keys::ESC)
        return true;
    if (userInput == Arcade::Keys::M) {
        _graphicLibInstance->stopSound(mainMusicId);
        _gameLibInstance.reset();
        _gameLibHandle.reset();
        bool res = this->setupMainMenu("");
        _graphicLibInstance->setGraphicMaps(_gameLibInstance->getColorMap(), _gameLibInstance->getCharDisplayMap());
        _gameLibInstance->start();
        _graphicLibInstance->start();
        mainMusicId = _graphicLibInstance->playSound(_gameLibInstance->getGameMusic());
        return res;
    }
    if (userInput == switchGame) {
        this->setGame(_currentGameStr = this->getNextGameLib());
        _graphicLibInstance->stopSound(mainMusicId);
        _graphicLibInstance->setGraphicMaps(_gameLibInstance->getColorMap(), _gameLibInstance->getCharDisplayMap());
        _graphicLibInstance->setSpritesMap(_gameLibInstance->getSpritesMap());
        _gameLibInstance->start();
        mainMusicId = _graphicLibInstance->playSound(_gameLibInstance->getGameMusic());
    } else if (userInput == switchGraphics) {
        _graphicLibInstance->stopSound(mainMusicId);
        this->setGraphics(_currentGraphicStr = this->getNextGraphicLib());
        _graphicLibInstance->setGraphicMaps(_gameLibInstance->getColorMap(), _gameLibInstance->getCharDisplayMap());
        _graphicLibInstance->start();
        _graphicLibInstance->setSpritesMap(_gameLibInstance->getSpritesMap());
        mainMusicId = _graphicLibInstance->playSound(_gameLibInstance->getGameMusic());
    } else if (userInput == restartGame) {
        this->setGame(_currentGameStr);
        _graphicLibInstance->stopSound(mainMusicId);
        _graphicLibInstance->setGraphicMaps(_gameLibInstance->getColorMap(), _gameLibInstance->getCharDisplayMap());
        _graphicLibInstance->setSpritesMap(_gameLibInstance->getSpritesMap());
        _gameLibInstance->start();
        mainMusicId = _graphicLibInstance->playSound(_gameLibInstance->getGameMusic());
    } else {
        _gameLibInstance->sendInput(userInput);
    }
    return false;
}

void Arcade::Core::start()
{
    if (!_loadedGraphics || !_loadedGame)
        throw GameLaunchError("ERROR Arcade: A graphics library & game must be chosen to start your game");
    _graphicLibInstance->setGraphicMaps(_gameLibInstance->getColorMap(), _gameLibInstance->getCharDisplayMap());
    _gameLibInstance->start();
    _graphicLibInstance->start();
    std::size_t mainMusicId = _graphicLibInstance->playSound(_gameLibInstance->getGameMusic());
    while (true) {
        std::vector<std::string> grid = _gameLibInstance->getGrid();
        _graphicLibInstance->setSpritesMap(_gameLibInstance->getSpritesMap());
        std::size_t tmpMusicId = _graphicLibInstance->playSound(_gameLibInstance->getInLoopMusic());
        _graphicLibInstance->displayGrid(grid);
        int score = _gameLibInstance->getScore();
        _graphicLibInstance->displayScore(score, grid);
        scoreSaver.SaveScore(_userName, this->getLibnameFromPath(_currentGameStr), score);
        _graphicLibInstance->displayHighScore(scoreSaver.getHighScore(_userName, this->getLibnameFromPath(_currentGameStr)), grid);
        Arcade::Keys userInput = _graphicLibInstance->getUserInput();
        if (this->manageInputs(userInput, mainMusicId))
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds{300});
        _graphicLibInstance->stopSound(tmpMusicId);
    }
}

int Arcade::Core::doArcade(std::string libName)
{
    try {
        Core arcadeCore(libName);

        return 0;
    } catch (const Error &err) {
        std::cerr << err.what() << std::endl;
        return 84;
    }
}

Arcade::Core::~Core()
{
    _graphicLibInstance.reset();
    _graphicLibHandle.reset();
    _gameLibInstance.reset();
    _gameLibHandle.reset();
}
