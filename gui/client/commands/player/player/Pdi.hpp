/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pdi.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Pdi : public Icommand {
        public:
            Pdi();
            ~Pdi();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};