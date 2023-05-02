/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** GameLaunchError
*/

#ifndef GAMELAUNCHERROR_HPP_
#define GAMELAUNCHERROR_HPP_

#include <iostream>
#include "Error.hpp"

namespace Arcade {
    class GameLaunchError : public Error {
        public:
            GameLaunchError(std::string msg) : _msg(msg) {}
            virtual ~GameLaunchError() = default;
            const char *what() const noexcept override { return _msg.c_str(); }

        private:
            std::string _msg;
    };
}

#endif /* !GAMELAUNCHERROR_HPP_ */
