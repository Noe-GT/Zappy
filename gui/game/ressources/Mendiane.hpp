/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Mendiane.hpp
*/
#pragma once
#include "IRessource.hpp"
namespace zappyGUI {
    class Mendiane: public IRessource{
        public:
            ~Mendiane() override = default;
            std::string getName() const override;
    };
}