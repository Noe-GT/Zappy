/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.hpp
*/

#pragma once
#include "UI/Window.hpp"
#include "Client/Client.hpp"
namespace ZappyGui {
    class GUI {
        public:
            GUI(int port, std::string hostname);

            void loop();

        private:
            void update();
            void events();
            void display();

            window _window;
            Client _client;
    };
};