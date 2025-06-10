/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Popup
*/

#include "Popup.hpp"

UIBlocks::Popup::Popup(std::string &content, std::pair<float, float> position, std::pair<float, float> size):
    _position(position),
    _content(UIBlocks::Text(content, position, 20)),
    _background(sf::Vector2f(_size.first, _size.second))
{
}
void UIBlocks::Popup::draw(zappyGUI::Window &window)
{
    if (!this->_isOpen)
        return;
    this->_background.setFillColor(this->_backgroundColor);
    window.getRenderWindow().draw(this->_background);
    this->_content.setPosition(std::pair<float, float>(this->_position.first + 10, this->_position.second + 10));
    this->_content.draw(window);
}
void UIBlocks::Popup::setPosition(const std::pair<float, float> &position)
{
    this->_background.setPosition(static_cast<float>(position.first), static_cast<float>(position.second));
}
void UIBlocks::Popup::handleEvent(const sf::Event &event, zappyGUI::Window &window)
{
    (void)event;
    (void)window;
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

void UIBlocks::Popup::setSize(const std::pair<float, float> &size)
{
    this->_size = size;
    this->_background.setSize(sf::Vector2f(size.first, size.second));
}

void UIBlocks::Popup::setSize(const int size)
{
    (void)size;
}