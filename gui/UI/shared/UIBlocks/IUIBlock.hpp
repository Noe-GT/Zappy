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
        virtual void draw(std::shared_ptr<zappyGUI::Window> &window) = 0;
        virtual void handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window) = 0;
        virtual void setPosition(const std::pair<float, float> &position) = 0;
        virtual void setSize(const std::pair<float, float> &size) = 0;
        virtual void setSize(const int size) = 0;
        virtual const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const = 0;
    };
}
