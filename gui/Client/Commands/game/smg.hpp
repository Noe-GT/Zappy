/*
** EPITECH PROJECT, 2024
** zap
** File description:
** smg.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class smg : public Icommand {
        public:
            smg();
            ~smg();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};