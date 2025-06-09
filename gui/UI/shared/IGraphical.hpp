/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IGraphical
*/

#pragma once
#include "Window.hpp"
#include "../../game/Tile.hpp"
#include <memory>
#include <vector>
#include <string>

namespace zappyGUI {
    class IGraphical {
        public:
            ~IGraphical() = default;
            virtual void initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize) = 0;
            virtual void display() = 0;
            virtual void displayTile(const zappyGUI::Tile &tile) = 0;
            virtual void update() = 0;
            virtual void handleEvents() = 0;
    };
};

