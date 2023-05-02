/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include "IGameLib.hpp"
#include "IGraphicLib.hpp"
#include "DLLoader.hpp"
#include "ScoreSaver.hpp"

/**
 * @brief Key used to switch game
 * 
 */
static const Arcade::Keys switchGame = Arcade::Keys::G;
/**
 * @brief Key used to switch graphical libraries
 * 
 */
static const Arcade::Keys switchGraphics = Arcade::Keys::V;
/**
 * @brief Key used to restart game
 * 
 */
static const Arcade::Keys restartGame = Arcade::Keys::R;

namespace Arcade {
    /**
     * @brief Core class used to link games to graphic libraries
     * 
     */
    class Core {
        public:
            /**
             * @brief Initializes the core, lists available game libraries, graphic libraries, and waits for the user to input his name. Then launches the main menu where the user can choose his game
             * 
             * @param graphicLib path to graphic library to load
             */
            Core(std::string graphicLib);
            /**
             * @brief Destroy the Core object, close all associated resources
             * 
             */
            ~Core();
            /**
             * @brief start the core and the main loop
             * 
             */
            void start();
            /**
             * @brief Set the game currently used & loaded. Unloads and closes previous the game with shared library handle associated if it exists. It then opens the library with the DLLoader class
             * 
             * @param gameLibPath path to the game library wanted
             */
            void setGame(std::string gameLibPath);
            /**
             * @brief Set the graphic library currently used & loaded. Unloads and closes the previous graphic library with shared library handle associated if it exists. It then opens the library with the DLLoader class
             * 
             * @param graphicLibPath path to the graphic library wanted
             */
            void setGraphics(std::string graphicLibPath);
            /**
             * @brief wait for user to input his name, sets the _userName variable
             * 
             */
            void listenForUserName();
            /**
             * @brief static method called from main to launch the core
             * 
             * @param graphicLibPath path to graphic library to load on core start
             * 
             * @return 84 on error
             * @return 0 on success
             */
            static int doArcade(std::string graphicLibPath);
            /**
             * @brief list available game libraries (raw path) in terminal
             * 
             */
            void listGameLibraries();
            /**
             * @brief list available graphic libraries (raw path) in terminal
             * 
             */
            void listGraphicLibraries();
            /**
             * @brief manage user input from graphic library
             * 
             * @param userInput Arcade::Keys item that represents the key the user pressed
             * @param mainMusicId id of the main background music. Used for game / graphic library switching
             * @return true if ESC was pressed
             * @return false otherwise
             */
            bool manageInputs(Arcade::Keys userInput, std::size_t &mainMusicId);
            /**
             * @brief Get the next game library available in "availableGameLibs" according to the current game
             * 
             * @return std::string : Next game raw path
             */
            std::string getNextGameLib();
            /**
             * @brief Get the next graphic library available in "availableGameLibs" according to the current graphic library
             * 
             * @return std::string : Next graphic library raw path
             */
            std::string getNextGraphicLib();
            /**
             * @brief Get the Actual name of the library from the path. F.E : ./lib/arcade_sfml.so -> sfml
             * 
             * @param path path to the library
             * @return std::string: name of raw library path passed as parameter
             */
            std::string getLibnameFromPath(std::string path);
            /**
             * @brief Parse libraries available in the "lib" folder and store them accordingly into availableGameLibs & availableGraphicLibs respectively
             * 
             * @param libs vector of the library paths available in the "lib"
             */
            void parseLibs(std::vector<std::string> libs);
            /**
             * @brief Setup the main menu to choose game & graphic library from. if graphicLibPath is an empty string, then the user can choose between available games & graphic libraries. If graphic library passed as parameter is valid, then it gives the user the oportunity to choose only between available games.
             * 
             * @param graphLibPath 
             * @return true if ESC was pressed during
             * @return false if ENTER was pressed and user exited menu
             */
            bool setupMainMenu(std::string graphLibPath);
            /**
             * @brief Get the display object represented by a vector of strings of the main menu according to available games & graphic libraries.
             * 
             * @param displayGraphic if true, displays graphical library choices, otherwise it isn't displayed
             * @param max_game maximum games available
             * @param max_graphic maximum graphical libraries available
             * @return std::vector<std::string> : display object
             */
            std::vector<std::string> getMainMenuDisplay(bool displayGraphic, int &max_game, int &max_graphic);

        private:
            /**
             * @brief unique pointer of DLLoader instance for the current graphic library
             * 
             */
            std::unique_ptr<DLLoader> _graphicLibHandle;
            /**
             * @brief unique pointer of the current graphic library instance
             * 
             */
            std::unique_ptr<IGraphicLib> _graphicLibInstance;
            /**
             * @brief variable that signifies if the graphic librairy has been loaded or not
             * 
             */
            bool _loadedGraphics = false;
            /**
             * @brief unique pointer of DLLoader instance for the current game library
             * 
             */
            std::unique_ptr<DLLoader> _gameLibHandle;
            /**
             * @brief unique pointer of the current game library instance
             * 
             */
            std::unique_ptr<IGameLib> _gameLibInstance;
            /**
             * @brief Current game library under string format
             * 
             */
            std::string _currentGameStr;
            /**
             * @brief Current graphical library under string format
             * 
             */
            std::string _currentGraphicStr;
            /**
             * @brief variable that signifies if the game librairy has been loaded or not
             * 
             */
            bool _loadedGame = false;
            /**
             * @brief Username that the user entered at program launch
             * 
             */
            std::string _userName;
            /**
             * @brief Score saver class used to save high scores of the user
             * 
             */
            Arcade::ScoreSaver scoreSaver;
            /**
             * @brief available game libraries. Each library is stored under path format
             * 
             */
            std::vector<std::string> availableGameLibs = {};
            /**
             * @brief available graphic libraries. Each library is stored under path format
             * 
             */
            std::vector<std::string> availableGraphicLibs = {};
    };
}

#endif /* !CORE_HPP_ */
