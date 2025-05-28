/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pgt.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class pgt : public Icommand {
        public:
            pgt();
            ~pgt();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};