/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IGraphical
*/

#pragma once
#include "Window.hpp"
#include "../../GUI.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

namespace zappyGUI {
    class IGraphical {
        public:
            virtual ~IGraphical() = default;
            virtual void initialize(std::shared_ptr<zappyGUI::GUI> gui) = 0;
            virtual void display() = 0;
            virtual void displayTile(const zappyGUI::Tile &tile) = 0;
            virtual void updateTile(const zappyGUI::Tile &tile) = 0;
            virtual void update() = 0;
            virtual void handleEvents() = 0;
    };
};

