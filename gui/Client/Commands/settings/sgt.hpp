/*
** EPITECH PROJECT, 2024
** zap
** File description:
** sgt.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class sgt : public Icommand {
        public:
            sgt();
            ~sgt();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};