/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pdr.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class pdr : public Icommand {
        public:
            pdr();
            ~pdr();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};