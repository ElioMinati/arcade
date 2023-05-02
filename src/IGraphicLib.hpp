/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IGraphicLib
*/

#ifndef IGRAPHICLIB_HPP_
    #define IGRAPHICLIB_HPP_
    #include <unordered_map>
    #include <vector>
    #include "Keys.hpp"
    #include "Graphics.hpp"
    #include "ILib.hpp"

namespace Arcade {
    /**
     * @brief Generic interface used for the implementation of graphic librairies.
     * 
     */
    class IGraphicLib: public ILib {
        public:
            /**
             * @brief Destroy the IGraphicLib object, closes all associated resources.
             * 
             */
            virtual ~IGraphicLib() = default;
            /**
             * @brief display the map. A map is represented by a vector of strings, these contain the characters to display that will then be parsed and displayed according to the color map, char map, and sprite map.
             * 
             * @param map map composed of a vector of strings
             */
            virtual void displayGrid(std::vector<std::string> map) = 0;
            /**
             * @brief Get the user input from the graphics library
             * 
             * @return Arcade::Keys key that the user pressed
             */
            virtual Arcade::Keys getUserInput() = 0;
            /**
             * @brief start the graphic library, inside this function are initialized all of the components necessary for the game display.
             * 
             */
            virtual void start() = 0;
            /**
             * @brief Set the colors & display characters that will then be used on display.
             * 
             * @param colorMap unordered_map of characters & color items represented by Arcade::Colors that will set the color to use for specified character in the map that will displayed
             * @param charMap unordered_map of characters. Maps a character to a display character. Usefull for Ncurses if you want to display a character other than the one stored in the map.
             */
            virtual void setGraphicMaps(std::unordered_map<char, Arcade::Colors> colorMap, std::unordered_map<char, char> charMap) = 0;
            /**
             * @brief Set the sprites to use on display
             * 
             * @param spriteMap unordered_map of characters to strings that represent the path of the asset to use as sprite. this map will used on displayGrid to replace characters by sprites. Can be called each frame to update particular sprites
             */
            virtual void setSpritesMap(std::unordered_map<char, std::string> spriteMap) = 0;
            /**
             * @brief Display score on screen
             * 
             * @param score Score of the player
             * @param grid Map. Used to calculate position of the score display.
             */
            virtual void displayScore(int score, std::vector<std::string> grid) = 0;
            /**
             * @brief Plays a sound. Used to play background music & ephemere sounds.
             * 
             * @param soundPath path of the sound to play.
             * @return std::size_t: id of the sound that can then be passed to "stopSound" to stop that particular sound
             */
            virtual std::size_t playSound(std::string soundPath) = 0;
            /**
             * @brief Stops a sound by its ID
             * 
             * @param soundId sound ID that was generated by "playSound" to stop said sound.
             */
            virtual void stopSound(std::size_t soundId) = 0;
            /**
             * @brief display high score of player on screen
             * 
             * @param score high score of player
             * @param grid Map that is used to calculate the position of the high score display
             */
            virtual void displayHighScore(int score, std::vector<std::string> grid) = 0;
    };
}

#endif /* !IGRAPHICLIB_HPP_ */