/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pex.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class pex : public Icommand {
        public:
            pex();
            ~pex();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};