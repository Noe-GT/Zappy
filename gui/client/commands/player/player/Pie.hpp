/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pie.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace zappyGUI {
    class Pie : public Icommand {
        public:
            Pie();
            ~Pie();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};