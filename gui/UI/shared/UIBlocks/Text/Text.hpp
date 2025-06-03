/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Text
*/

#pragma once

#include "../IUIBlock.hpp"

class Text: public UIBlocks::IUIBlock {
    public:
        Text(std::string text, std::string font, std::pair<int, int> position, std::pair<int, int> size);
        ~Text() = default;
        void draw(zappyGUI::Window &window) override;
        void handleEvent(const sf::Event &event) override;
        void setText(const std::string &text);
        void setPosition(std::pair<int, int> position);

    private:
        std::pair<int, int> _position;
        std::pair<int, int> _size;
        sf::Text _text;
        sf::Font _font;
        sf::RectangleShape _background;
};
