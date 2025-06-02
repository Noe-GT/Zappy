/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pgt.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Pgt : public Icommand {
        public:
            Pgt();
            ~Pgt();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};