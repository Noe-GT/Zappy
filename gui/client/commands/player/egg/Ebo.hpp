/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Ebo.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace zappyGUI {
    class Ebo : public Icommand {
        public:
            Ebo();
            ~Ebo();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};