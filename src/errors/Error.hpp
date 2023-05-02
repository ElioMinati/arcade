/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <exception>

namespace Arcade {
    class Error : public std::exception {
        public:
            Error() {};
            virtual ~Error() = default;
            const char *what() const noexcept = 0;
    };
}

#endif /* !ERROR_HPP_ */
