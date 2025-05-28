/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pnw.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Pnw : public Icommand {
        public:
            Pnw();
            ~Pnw();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};