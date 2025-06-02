/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IUIBlock
*/

#pragma once

#include "../Window.hpp"

namespace UIBlocks {
    class IUIBlock {
        public:
            virtual void draw(zappyGUI::Window &window) = 0;
            virtual void handleEvent(const sf::Event &event) = 0;
    };
}
