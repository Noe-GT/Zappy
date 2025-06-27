/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sibur.hpp
*/
#pragma once
#include "IRessource.hpp"
namespace zappyGUI {
    class Sibur: public IRessource{
        public:
            ~Sibur() override = default;
            std::string getName() const override;
    };
}