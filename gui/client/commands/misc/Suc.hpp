/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Suc.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Suc : public Icommand {
        public:
            Suc();
            ~Suc();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};