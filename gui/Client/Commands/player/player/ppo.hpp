/*
** EPITECH PROJECT, 2024
** zap
** File description:
** ppo.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class ppo : public Icommand {
        public:
            ppo();
            ~ppo();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};