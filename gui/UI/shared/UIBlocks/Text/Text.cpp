/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Text
*/

#include "Text.hpp"

UIBlocks::Text::Text(std::string text, std::pair<float, float> position, int size)
{
    this->_text.setFont(this->_font);
    this->_text.setCharacterSize(size);
    this->_text.setString(text);

    this->setPosition(position);
}

UIBlocks::Text::Text(std::string text, std::pair<float, float> position, int size, std::string font)
{
    if (!this->_font.loadFromFile(font))
        throw std::runtime_error("Failed to load font: " + font);
    this->_text.setFont(this->_font);
    this->_text.setCharacterSize(size);
    this->_text.setString(text);

    this->setPosition(position);
}

void UIBlocks::Text::setText(const std::string &text)
{
    this->_text.setString(text);
}

void UIBlocks::Text::draw(std::shared_ptr<zappyGUI::Window> &window)
{
    this->_text.setFont(this->_font);
    this->_text.setFillColor(this->_textColor);
    this->_text.setOutlineThickness(this->_borderThickness);
    this->_text.setOutlineColor(this->_borderColor);
    window.get()->getRenderWindow().draw(this->_text);
}

void UIBlocks::Text::setPosition(const std::pair<float, float> &position)
{
    this->_text.setPosition(sf::Vector2f(position.first, position.second));
}

void UIBlocks::Text::handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window)
{
    (void)event;
    (void)window;
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Text::getValue() const
{
    std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->_text.getString();
    return value;
}

void UIBlocks::Text::setSize(const std::pair<float, float> &size)
{
    (void)size;
}

void UIBlocks::Text::setSize(const int size)
{
    this->_text.setCharacterSize(size);
}