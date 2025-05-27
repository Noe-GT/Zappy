/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pdi.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class pdi : public Icommand {
        public:
            pdi();
            ~pdi();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};