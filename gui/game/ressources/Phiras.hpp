/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Phiras.hpp
*/
#pragma once

#include "IRessource.hpp"
namespace zappyGUI {
    class Phiras: public IRessource{
        public:
            ~Phiras() override = default;
            std::string getName() const override;
    };
}