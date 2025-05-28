/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Smg.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Smg : public Icommand {
        public:
            Smg();
            ~Smg();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};