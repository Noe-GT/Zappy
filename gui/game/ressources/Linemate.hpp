/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Linemate.hpp
*/
#pragma once
#include "IRessource.hpp"
namespace zappyGUI {
    class Linemate: public IRessource{
        public:
            ~Linemate() override = default;
            std::string getName() const override;
    };
}