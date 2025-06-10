/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sgt.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Sgt : public Icommand {
        public:
            Sgt();
            ~Sgt();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui, Cserver &sender);
    };
};