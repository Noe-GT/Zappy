/*
** EPITECH PROJECT, 2024
** zap
** File description:
** IRessource.hpp
*/
#pragma once
#include <string>
namespace zappyGUI {
    class IRessource {
        public:
            virtual ~IRessource() = default;
            virtual std::string getName() const = 0;
    };
};