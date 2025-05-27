/*
** EPITECH PROJECT, 2024
** zap
** File description:
** seg.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class seg : public Icommand {
        public:
            seg();
            ~seg();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};