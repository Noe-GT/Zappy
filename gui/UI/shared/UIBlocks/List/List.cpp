/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** List
*/

#include "List.hpp"

List::List(std::vector<UIBlocks::IUIBlock> elements, std::pair<int, int> position, std::pair<int, int> size):
    _position(position),
    _size(size),
    _elements(elements),
    _background(sf::Vector2f(_size.first, _size.second))
{
}

void List::draw(zappyGUI::Window &window)
{
    this->_background.setPosition(this->_position.first, this->_position.second);
    this->_background.setFillColor(sf::Color(50, 50, 50, 200));
    window.getRenderWindow().draw(_background);

    for (size_t i = 0; i < _elements.size(); ++i) {
        _elements[i].draw(window);
    }
}

void List::handleEvent(const sf::Event &event)
{
    for (auto &element : _elements) {
        element.handleEvent(event);
    }
}

void List::addElement(UIBlocks::IUIBlock &element)
{
    _elements.push_back(element);
}

void List::removeElement(size_t index)
{
    if (index < _elements.size())
        _elements.erase(_elements.begin() + index);
}