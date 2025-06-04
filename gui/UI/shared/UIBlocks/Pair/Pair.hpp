/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Pair
*/

#pragma once

#include "../IUIBlock.hpp"
#include <memory>

namespace UIBlocks {
    class Pair: public IUIBlock {
        public:
            Pair(std::pair<std::shared_ptr<IUIBlock>, std::shared_ptr<IUIBlock>> &pair, std::pair<int, int> position);
            ~Pair() = default;
            void draw(zappyGUI::Window &window) override;
            void setPosition(const std::pair<int, int> &position) override;
            void handleEvent(const sf::Event &event) override;
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;


        private:
            std::pair<int, int> _position;
            std::pair<std::shared_ptr<IUIBlock>, std::shared_ptr<IUIBlock>> _pair;
    };
}
