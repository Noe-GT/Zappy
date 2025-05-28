/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.hpp
*/

#pragma once
#include "UI/Window.hpp"
#include "Client/Client.hpp"
#include "Game/Game.hpp"
namespace zappyGUI {
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
            Game _game;
            //FIXME: add the cirular buffer here
    };
};