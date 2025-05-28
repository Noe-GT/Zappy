/*
** EPITECH PROJECT, 2024
** zap
** File description:
** msz.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class msz : public Icommand {
        public:
            msz();
            ~msz();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};