/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pie.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class pie : public Icommand {
        public:
            pie();
            ~pie();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};