/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IUIBlock
*/

#pragma once

#include "UI/shared/Window.hpp"

namespace UIBlocks {
    class IUIBlock {
        public:
            virtual void draw(ZappyGui::Window &window) = 0;
            virtual void handleEvent(const sf::Event &event) = 0;
    };
}
