/*
** EPITECH PROJECT, 2024
** zap
** File description:
** enw.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace zappyGUI {
    class enw : public Icommand {
        public:
            enw();
            ~enw();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};