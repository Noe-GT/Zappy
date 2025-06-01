/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sst.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Sst : public Icommand {
        public:
            Sst();
            ~Sst();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};