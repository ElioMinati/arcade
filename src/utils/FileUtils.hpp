/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** FileUtils
*/

#ifndef FILEUTILS_HPP_
    #define FILEUTILS_HPP_
    #include <iostream>
    #include <filesystem>
    #include <vector>

/**
 * @brief File utilitaries
 * 
 */
class FileUtils {
    public:
        /**
         * @brief Object Constructor.
         * 
         */
        FileUtils();
        /**
         * @brief Object Destructor
         * 
         */
        ~FileUtils();
        /**
         * @brief Check if file exists
         * 
         * @param filename path of file to check
         * @return true if file exists
         * @return false if files doesn't exit
         */
        static bool FileExists(std::string filename);
        /**
         * @brief Read content of file stored under string form.
         * 
         * @param filename path of file to read from
         * @return std::string: content of file
         */
        static std::string readFromFile(std::string filename);
        /**
         * @brief Read all directory files
         * 
         * @param dirpath path of directory to read files from
         * @return std::vector<std::string>: list of all files fouond in directory
         */
        static std::vector<std::string> readDirectory(std::string dirpath);
        /**
         * @brief Read content of file and store content line by line
         * 
         * @param filename path of file to read from
         * @return std::vector<std::string> list of lines read
         */
        static std::vector<std::string> readFromFileToVector(std::string filename);
};

#endif /* !FILEUTILS_HPP_ */
