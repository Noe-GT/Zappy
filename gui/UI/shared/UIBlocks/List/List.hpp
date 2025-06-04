/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** List
*/

#pragma once

#include "../IUIBlock.hpp"
#include <memory>

namespace UIBlocks {
    class List: public IUIBlock {
        public:
            List(std::vector<std::shared_ptr<IUIBlock>> &elements, std::pair<int, int> position, std::pair<int, int> size);
            ~List() = default;
            void draw(zappyGUI::Window &window) override;
            void setPosition(const std::pair<int, int> &position) override;
            void handleEvent(const sf::Event &event) override;
            
            void addElement(std::shared_ptr<IUIBlock> element);
            void removeElement(size_t index);
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;

        private:
            std::pair<int, int> _position;
            std::pair<int, int> _size;
            std::vector<std::shared_ptr<IUIBlock>> _elements;
            sf::RectangleShape _background;
    };
}
