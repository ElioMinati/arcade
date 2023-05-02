/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** main
*/

#include <iostream>
#include "ErrorHandling.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2 || av[1] == NULL) {
        std::cerr << ERR_INVALID_ARGS << std::endl;
        return 84;
    }
    return Arcade::Core::doArcade(av[1]);
}
