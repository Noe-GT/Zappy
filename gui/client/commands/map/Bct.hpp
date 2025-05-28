/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Bct.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Bct : public Icommand {
        public:
            Bct();
            ~Bct();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};