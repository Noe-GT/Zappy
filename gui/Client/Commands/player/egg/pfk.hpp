/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pfk.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace ZappyGui {
    class pfk : public Icommand {
        public:
            pfk();
            ~pfk();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};