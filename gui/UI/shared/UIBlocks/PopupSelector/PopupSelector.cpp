/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PopupSelector
*/

#include "PopupSelector.hpp"

UIBlocks::PopupSelector::PopupSelector(std::vector<std::string> &options):
    _position(0, 0),
    _size(200, 300),
    _options(options),
    _background(sf::Vector2f(_size.first, _size.second)),
    _selected(""),
    _isOpen(false)
{
}

void UIBlocks::PopupSelector::draw(ZappyGui::Window &window)
{
    if (!_isOpen)
        return;
    this->_background.setPosition(_position.first, _position.second);
    this->_background.setFillColor(sf::Color(50, 50, 50, 200));
    window.getRenderWindow().draw(_background);

    std::vector<std::string> visibleOptions = _options.getVisibleOptions();
    for (size_t i = 0; i < visibleOptions.size(); ++i) {
        sf::Text optionText;
        optionText.setString(visibleOptions[i]);
        optionText.setPosition(_position.first + 10, _position.second + 10 + i * 30);
        optionText.setFillColor(sf::Color::White);
        window.getRenderWindow().draw(optionText);
    }
}

void UIBlocks::PopupSelector::open()
{
    _isOpen = true;
}

void UIBlocks::PopupSelector::close()
{
    _isOpen = false;
}

const std::string &UIBlocks::PopupSelector::getSelected() const
{
    return _selected;
}

bool UIBlocks::PopupSelector::isInside(int x, int y) const
{
    return (x >= _position.first and x <= _position.first + _size.first and
            y >= _position.second and y <= _position.second + _size.second);
}


void UIBlocks::PopupSelector::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isInside(event.mouseButton.x, event.mouseButton.y)) {
                int index = (event.mouseButton.y - _position.second) / 30;
                if (index >= 0 and index < _options.getVisibleOptions().size()) 
                    _selected = _options.getVisibleOptions()[index];
            }
        }
    } else if (isInside(event.mouseButton.x, event.mouseButton.y) and event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            _options.scrollUp();
        else
            _options.scrollDown();
    }
}


