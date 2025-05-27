/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pbc.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class pbc : public Icommand {
        public:
            pbc();
            ~pbc();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};