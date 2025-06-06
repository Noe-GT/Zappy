/*
** EPITECH PROJECT, 2024
** zap
** File description:
** DlLoader.hpp
*/

#pragma once
#include <dlfcn.h>
#include <string>
#include <iostream>
#include <memory>
#include <functional>

namespace zappyGUI {
    class DLLoader {
        public:
            DLLoader(const std::string& libName)
            {
                this->_lib = dlopen(libName.c_str(), RTLD_LAZY | RTLD_NODELETE);
                if (!this->_lib) {
                    std::string error = "Failed to open shared lib: ";
                    error += libName;
                    const char* dlError = dlerror();
                    if (dlError) {
                        error += " - ";
                        error += dlError;
                    }
                    throw std::runtime_error(error);
                }
            }

            ~DLLoader()
            {
                if (_lib) {
                    dlclose(_lib);
                }
            }

            DLLoader(const DLLoader&) = delete;
            DLLoader& operator=(const DLLoader&) = delete;

            template<typename T>
            std::unique_ptr<T> getInstance(const std::string& instanceName) const
            {
                dlerror();
                void* symbol = dlsym(_lib, instanceName.c_str());
                const char* dlsym_error = dlerror();
                if (dlsym_error || !symbol) {
                    std::string error = "Failed to load symbol '";
                    error += instanceName;
                    error += "' ";
                    if (dlsym_error) {
                        error += dlsym_error;
                    }
                    throw std::runtime_error(error);
                }
                typedef T* (*create_function_t)();
                create_function_t create_function = reinterpret_cast<create_function_t>(symbol);
                T* instance = create_function();
                if (!instance) {
                    throw std::runtime_error("Function '" + instanceName + "' returned null pointer");
                }
                return std::unique_ptr<T>(instance);
            }
        private:
            void* _lib;
    };
}
