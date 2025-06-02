/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Enw.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace zappyGUI {
    class Enw : public Icommand {
        public:
            Enw();
            ~Enw();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};