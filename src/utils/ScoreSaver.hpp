/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** ScoreSaver
*/

#ifndef SCORESAVER_HPP_
    #define SCORESAVER_HPP_
    #include <iostream>
    #include <fstream>
    #include <unordered_map>

/**
 * @brief path to the file that is going to contain all saved high scores
 * 
 */
static const std::string scoreSavingPath = "high-score.db";

namespace Arcade {
    /**
     * @brief Class used for high score saving
     * 
     */
    class ScoreSaver {
        public:
            /**
             * @brief Initializes the class. Loads the file that stores the high scores.
             * 
             */
            ScoreSaver();
            /**
             * @brief Destroys the ScoreSaver object and destroys all attached resources
             * 
             */
            virtual ~ScoreSaver() = default;
            /**
             * @brief Save the score of the user playing specific game. Only saves score if the score is higher than the previous high score
             * 
             * @param user User represented by a string
             * @param game Game the score was achieved on
             * @param score Score the user achieved
             */
            virtual void SaveScore(std::string user, std::string game, int score);
            /**
             * @brief Get the High Score of the user on specified game
             * 
             * @param user User to retrieve high score from
             * @param game Game to retrieve high score from
             * @return int: Score of the user on specified game
             */
            virtual int getHighScore(std::string user, std::string game);
            /**
             * @brief Save the globalScores map to the high score database file.
             * 
             */
            virtual void saveToFile();
            /**
             * @brief Add score of user in specified game to the globalScores map. Replaces it if score already exists.
             * 
             * @param user User to set high score to
             * @param game Game to set high score to
             * @param score Score of the user
             */
            virtual void addToMultimap(std::string user, std::string game, int score);
        private:
            /**
             * @brief global score object containing all high scores of all users on all played games.
             * 
             */
            std::unordered_map<std::string, std::unordered_map<std::string, int>> globalScores;

    };
}

#endif /* !SCORESAVER_HPP_ */
