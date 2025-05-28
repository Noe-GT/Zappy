/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pic.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Pic : public Icommand {
        public:
            Pic();
            ~Pic();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};