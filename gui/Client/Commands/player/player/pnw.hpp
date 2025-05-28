/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pnw.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class pnw : public Icommand {
        public:
            pnw();
            ~pnw();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};