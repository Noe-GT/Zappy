/*
** EPITECH PROJECT, 2024
** zap
** File description:
** bct.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class bct : public Icommand {
        public:
            bct();
            ~bct();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};