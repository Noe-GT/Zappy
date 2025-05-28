/*
** EPITECH PROJECT, 2024
** zap
** File description:
** edi.hpp
*/

#pragma once
#include "../../Icommand.hpp"

namespace zappyGUI {
    class edi : public Icommand {
        public:
            edi();
            ~edi();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};