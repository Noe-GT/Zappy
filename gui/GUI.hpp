/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.hpp
*/

#pragma once
#include "UI/shared/Window.hpp"
#include "Client/Client.hpp"
#include "game/Game.hpp"
namespace zappyGUI {
    class GUI {
        public:
            GUI(int port, std::string hostname);

            void loop();

            window getWindow();
            Client getClient();
            Game getGame();

        private:
            void update();
            void events();
            void display();

            window _window;
            Client _client;
            Game _game;
    };
};