/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Pair
*/

#pragma once

#include "../AUIBlock.hpp"
#include <memory>

namespace UIBlocks {
    class Pair: public AUIBlock {
        public:
            Pair(std::pair<std::shared_ptr<IUIBlock>, std::shared_ptr<IUIBlock>> &pair, std::pair<float, float> position);
            ~Pair() = default;
            void draw(std::shared_ptr<zappyGUI::Window> &window) override;
            void setPosition(const std::pair<float, float> &position) override;
            void handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window) override;
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;
            void setSize(const std::pair<float, float> &size) override;
            void setSize(const int size) override;

        private:
            std::pair<float, float> _position;
            std::pair<std::shared_ptr<IUIBlock>, std::shared_ptr<IUIBlock>> _pair;
    };
}
