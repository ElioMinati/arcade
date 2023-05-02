/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** IGameLib
*/

#ifndef IGAMELIB_HPP_
    #define IGAMELIB_HPP_
    #include <vector>
    #include "Keys.hpp"
    #include "Graphics.hpp"
    #include "ILib.hpp"

namespace Arcade {
    /**
     * @brief Generic interface used for the implementation of games librairies.
     * 
     */
    class IGameLib : public ILib {
        public:
            /**
             * @brief Destroy the IGameLib object, closes all associated resources.
             * 
             */
            virtual ~IGameLib() = default;
            /**
             * @brief Get the _map of the current game instance.
             * 
             * @return std::vector<std::string> 
             */
            virtual std::vector<std::string> getGrid() = 0;
            /**
             * @brief Get the _score variable.
             * 
             * @return int 
             */
            virtual int getScore() = 0;
            /**
             * @brief Start the instance of the game.
             * 
             */
            virtual void start() = 0;
            /**
             * @brief Store the key given as parameter in the instancied game.
             * 
             * @param key 
             */
            virtual void sendInput(Arcade::Keys key) = 0;
            /**
             * @brief Get the Color Map object
             * 
             * @return std::unordered_map<char, Arcade::Colors> 
             */
            virtual std::unordered_map<char, Arcade::Colors> getColorMap() = 0;
            /**
             * @brief Get the Char Display Map object
             * 
             * @return std::unordered_map<char, char> 
             */
            virtual std::unordered_map<char, char> getCharDisplayMap() = 0;
            /**
             * @brief Get the Sprites Map object
             * 
             * @return std::unordered_map<char, std::string> 
             */
            virtual std::unordered_map<char, std::string> getSpritesMap() = 0;
            /**
             * @brief Get the Game Music object
             * 
             * @return std::string 
             */
            virtual std::string getGameMusic() = 0;
            /**
             * @brief Get the In Loop Music object
             * 
             * @return std::string 
             */
            virtual std::string getInLoopMusic() = 0;
            /**
             * @brief Set the _map of the instancied game to the map given as parameter.
             * 
             * @param map 
             */
            virtual void setMap(std::vector<std::string> map) = 0;
    };
}

#endif /* !IGAMELIB_HPP_ */
