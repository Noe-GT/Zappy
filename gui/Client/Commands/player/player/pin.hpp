/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pin.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class pin : public Icommand {
        public:
            pin();
            ~pin();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};