/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pin.hpp
*/

#pragma once
#include "../Icommand.hpp"

namespace zappyGUI {
    class Pin : public Icommand {
        public:
            Pin();
            ~Pin();

            void receive(std::string command, GUI &gui);
            void send(std::string command, GUI &gui);
    };
};