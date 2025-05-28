/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pic.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class pic : public Icommand {
        public:
            pic();
            ~pic();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};