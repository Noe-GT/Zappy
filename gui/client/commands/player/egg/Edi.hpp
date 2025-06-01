/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Edi.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace zappyGUI {
    class Edi : public Icommand {
        public:
            Edi();
            ~Edi();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};