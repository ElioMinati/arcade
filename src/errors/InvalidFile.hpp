/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** InvalidFile
*/

#ifndef INVALIDFILE_HPP_
#define INVALIDFILE_HPP_
#include <iostream>
#include "Error.hpp"

namespace Arcade {
    class InvalidFile : public Error {
        public:
            InvalidFile(std::string msg) : _msg(msg) {}
            virtual ~InvalidFile() = default;
            const char *what() const noexcept override { return _msg.c_str(); }

        private:
            std::string _msg;
    };
}

#endif /* !INVALIDFILE_HPP_ */
