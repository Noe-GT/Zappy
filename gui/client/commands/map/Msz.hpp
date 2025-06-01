/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Msz.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Msz : public Icommand {
        public:
            Msz();
            ~Msz();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};