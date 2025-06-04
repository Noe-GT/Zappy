/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Text
*/

#include "Text.hpp"

UIBlocks::Text::Text(std::string text, std::string font, std::pair<int, int> position, int size)
{
    this->_font.loadFromFile(font);
    this->_text.setFont(this->_font);
    this->_text.setCharacterSize(size);
    this->_text.setString(text);

    this->setPosition(position);
}

void UIBlocks::Text::setText(const std::string &text)
{
    this->_text.setString(text);
}

void UIBlocks::Text::draw(zappyGUI::Window &window)
{
    this->_text.setFont(this->_font);
    this->_text.setFillColor(sf::Color::Black);
    window.getRenderWindow().draw(this->_text);
}

void UIBlocks::Text::setPosition(const std::pair<int, int> &position)
{
    this->_text.setPosition(sf::Vector2f(position.first, position.second));
}

void UIBlocks::Text::handleEvent(const sf::Event &event)
{
    (void)event;
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Text::getValue() const
{
    std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->_text.getString();
    return value;
}