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
#include <variant>

namespace UIBlocks {
    class IUIBlock {
        public:
        virtual void draw(zappyGUI::Window &window) = 0;
        virtual void handleEvent(const sf::Event &event) = 0;
        virtual void setPosition(const std::pair<float, float> &position) = 0;
        virtual const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const = 0;
    };
}
