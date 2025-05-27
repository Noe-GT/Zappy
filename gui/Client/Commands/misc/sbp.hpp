/*
** EPITECH PROJECT, 2024
** zap
** File description:
** sbp.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class sbp : public Icommand {
        public:
            sbp();
            ~sbp();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};