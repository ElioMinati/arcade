/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_
#include <iostream>
#include <dlfcn.h>
#include "InvalidFile.hpp"

/**
 * @brief Shared library loader
 * 
 */
class DLLoader {
    private:
        /**
         * @brief library handle created by dlopen
         * 
         */
        void *handle;
        /**
         * @brief Library instance returned by the call of the entrypoint
         * 
         */
        Arcade::ILib *lib;
    public:
        /**
         * @brief Load a shared library according to the library path
         * 
         * @param libPath path of shared library to load
         */
        DLLoader(std::string libPath) {
            handle = dlopen(libPath.c_str(), RTLD_NOW | RTLD_LOCAL);

            if (handle == NULL)
                throw Arcade::InvalidFile(dlerror());
            lib = reinterpret_cast<Arcade::ILib *(*)()>(dlsym(handle, "entryPoint"))();
        }
        /**
         * @brief Destroy the loaded library, closes the handle.
         * 
         */
        virtual ~DLLoader() {
            if (handle != NULL) {
                dlclose(handle);
            }
        };
        /**
         * @brief Get the Instance object
         * 
         * @tparam T Template, can be any interface that has ILib as an inherited class
         * @return T*: pointer to stored interface returned by the dlsym of the entrypoint.
         */
        template <typename T>
        T *getInstance() {
            return dynamic_cast<T *>(lib);
        }
};

#endif /* !DLLOADER_HPP_ */
