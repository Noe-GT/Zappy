/*
** EPITECH PROJECT, 2024
** zap
** File description:
** tna.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class tna : public Icommand {
        public:
            tna();
            ~tna();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};