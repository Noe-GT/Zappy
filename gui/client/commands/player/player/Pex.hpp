/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pex.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Pex : public Icommand {
        public:
            Pex();
            ~Pex();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};