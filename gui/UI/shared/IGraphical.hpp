/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IGraphical
*/

#pragma once
#include "../../GUI.hpp"
#include "../../Tile.hpp"
#include <memory>
#include <vector>
#include <string>

namespace zappyGUI {
    class IGraphical {
        public:
            ~IGraphical() = default;
            virtual void initialize(std::shared_ptr<zappyGUI::GUI> gui) = 0;
            virtual void display() = 0;
            virtual void update() = 0;
            virtual void handleEvents() = 0;
    };
};

