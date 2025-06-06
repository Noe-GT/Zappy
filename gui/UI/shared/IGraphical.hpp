/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IGraphical
*/

#pragma once
#include "../../game/Game.hpp"
#include "Window.hpp"

namespace zappyGUI {
    class IGraphical {
        public:
            ~IGraphical() = default;
            virtual void initialize(std::shared_ptr<zappyGUI::Window> window, std::shared_ptr<zappyGUI::Game> game) = 0;
            virtual void display() = 0;
            virtual void update() = 0;
            virtual void handleEvents() = 0;
    };
};

