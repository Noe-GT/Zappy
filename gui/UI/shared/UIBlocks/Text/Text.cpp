/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Text
*/

#include "Text.hpp"

Text::Text(std::string text, std::string font, std::pair<int, int> position, std::pair<int, int> size):
    _font(),
    _text(text, _font)
{
    this->_font.loadFromFile(font);
}

void Text::setText(const std::string &text)
{
    this->_text.setString(text);
}

void Text::draw(zappyGUI::Window &window)
{
    
}

void Text::setPosition(std::pair<int, int> position)
{
    this->_position = position;
}

