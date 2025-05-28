/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Mct.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Mct : public Icommand {
        public:
            Mct();
            ~Mct();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};