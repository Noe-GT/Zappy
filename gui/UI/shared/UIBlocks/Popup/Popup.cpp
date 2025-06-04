/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Popup
*/

#include "Popup.hpp"

UIBlocks::Popup::Popup(std::string &content, const std::string font, std::pair<int, int> position, std::pair<int, int> size):
    _position(position),
    _content(UIBlocks::Text(content, font, position, size.second / 2)),
    _background(sf::Vector2f(_size.first, _size.second)),
    _pair(nullptr, nullptr)
{
}
void UIBlocks::Popup::draw(zappyGUI::Window &window)
{
    if (!this->_isOpen)
        return;
    this->_background.setFillColor(sf::Color(50, 50, 50, 200));
    window.getRenderWindow().draw(_background);
    this->_content.setPosition(std::pair<int, int>(this->_position.first + 10, this->_position.second + 10));
    this->_content.draw(window);
}
void UIBlocks::Popup::setPosition(const std::pair<int, int> &position)
{
    this->_background.setPosition(static_cast<float>(position.first), static_cast<float>(position.second));
}
void UIBlocks::Popup::handleEvent(const sf::Event &event)
{
    (void)event;
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Popup::getValue() const
{
    std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->_content.getValue();
    return value;
}

void UIBlocks::Popup::open()
{
    this->_isOpen = true;
}

void UIBlocks::Popup::close()
{
    this->_isOpen = false;
}