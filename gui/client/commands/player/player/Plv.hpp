/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Plv.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Plv : public Icommand {
        public:
            Plv();
            ~Plv();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};