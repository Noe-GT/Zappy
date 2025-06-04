/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IUIBlock
*/

#pragma once

#include "../Window.hpp"

#include <memory>
#include <vector>
#include <string>

namespace UIBlocks {
    class IUIBlock {
        public:
        virtual void draw(zappyGUI::Window &window) = 0;
        virtual void handleEvent(const sf::Event &event) = 0;
        virtual void setPosition(const std::pair<int, int> &position) = 0;
        virtual std::string getValue() const = 0;
        virtual std::vector<std::shared_ptr<IUIBlock>> getList() const = 0;
    };
}
