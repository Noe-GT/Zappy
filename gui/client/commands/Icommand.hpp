/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Icommand.hpp
*/

#pragma once
#include <string>
#include <sstream>

namespace zappyGUI {
    class GUI;
    class Cserver;

    class Icommand {
        public:
            virtual ~Icommand() = default;

            virtual void receive(std::string command, GUI &gui) = 0;
            virtual void send(std::string command, GUI &gui, Cserver &sender) = 0;
    };
};