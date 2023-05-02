/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** FileUtils
*/


#include <fstream>
#include "FileUtils.hpp"

FileUtils::FileUtils()
{
}

bool FileUtils::FileExists(const std::string filepath)
{
    std::ifstream file(filepath.c_str());

    return file.good();
}

std::string FileUtils::readFromFile(std::string filepath)
{
    std::ifstream fileStream(filepath.c_str());
    std::string fileContent = "";
    char c;

    while (!fileStream.eof() && (c = fileStream.get()) != fileStream.eof())
        fileContent.push_back(c);
    return fileContent;
}

std::vector<std::string> FileUtils::readFromFileToVector(std::string filepath)
{
    std::ifstream fileStream(filepath.c_str());
    std::string fileContent = "";
    std::vector<std::string> destVector = {};
    char c;

    while (!fileStream.eof() && (c = fileStream.get()) != fileStream.eof()) {
        if (c == '\n') {
            destVector.push_back(fileContent);
            fileContent = "";
            continue;
        }
        fileContent.push_back(c);
    }
    if (!fileContent.empty())
        destVector.push_back(fileContent);
    return destVector;
}

std::vector<std::string> FileUtils::readDirectory(std::string dirPath)
{
    if (!std::filesystem::exists(dirPath))
        return {};

    std::vector<std::string> dest = {};
    for (const auto &file : std::filesystem::directory_iterator(dirPath))
        dest.push_back(file.path());
    return dest;
}

FileUtils::~FileUtils()
{
}
