/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sbp.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Sbp : public Icommand {
        public:
            Sbp();
            ~Sbp();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};