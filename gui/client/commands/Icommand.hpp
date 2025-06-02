/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Icommand.hpp
*/

#pragma once
#include <string>
#include "../Cserver.hpp"
#include "../../GUI.hpp"
#include <sstream>
namespace zappyGUI {
    class Icommand {
        public:
            virtual ~Icommand() = default;

            virtual void receive(std::string command, GUI &gui) = 0;
            virtual void send(std::string command, GUI &gui, Cserver &sender) = 0;
    };
};