/*
** EPITECH PROJECT, 2024
** zap
** File description:
** sst.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class sst : public Icommand {
        public:
            sst();
            ~sst();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};