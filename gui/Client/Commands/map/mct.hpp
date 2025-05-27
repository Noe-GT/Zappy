/*
** EPITECH PROJECT, 2024
** zap
** File description:
** mct.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace ZappyGui {
    class mct : public Icommand {
        public:
            mct();
            ~mct();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};