/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pdr.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Pdr : public Icommand {
        public:
            Pdr();
            ~Pdr();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};