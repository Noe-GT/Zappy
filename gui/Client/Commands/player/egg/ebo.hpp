/*
** EPITECH PROJECT, 2024
** zap
** File description:
** ebo.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace ZappyGui {
    class ebo : public Icommand {
        public:
            ebo();
            ~ebo();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};