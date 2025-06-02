/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pbc.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace zappyGUI {
    class Pbc : public Icommand {
        public:
            Pbc();
            ~Pbc();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};