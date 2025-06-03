/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** List
*/

#pragma once

#include "../IUIBlock.hpp"

class List: public UIBlocks::IUIBlock {
    public:
        List(std::vector<UIBlocks::IUIBlock> elements, std::pair<int, int> position, std::pair<int, int> size);
        ~List() = default;
        void draw(zappyGUI::Window &window) override;
        void handleEvent(const sf::Event &event) override;
        void addElement(UIBlocks::IUIBlock &element);
        void removeElement(size_t index);

    private:
        std::pair<int, int> _position;
        std::pair<int, int> _size;
        std::vector<UIBlocks::IUIBlock> _elements;
        sf::RectangleShape _background;
};
