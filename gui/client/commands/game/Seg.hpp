/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Seg.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Seg : public Icommand {
        public:
            Seg();
            ~Seg();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};