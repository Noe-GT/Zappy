/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** List
*/

#include "List.hpp"

UIBlocks::List::List(std::vector<std::shared_ptr<IUIBlock>> &elements, std::pair<float, float> position, std::pair<float, float> size):
    _position(position),
    _size(size),
    _elements(elements),
    _background(sf::Vector2f(_size.first, _size.second))
{
}

void UIBlocks::List::draw(std::shared_ptr<zappyGUI::Window> &window)
{
    this->_background.setPosition(this->_position.first, this->_position.second);
    this->_background.setFillColor(this->_backgroundColor);
    window.get()->getRenderWindow().draw(_background);

    for (size_t i = 0; i < _elements.size(); ++i) {
        _elements[i]->setPosition(std::pair<float, float>(_position.first, _position.second + i * 20));
        _elements[i]->draw(window);
    }
}

void UIBlocks::List::handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window)
{
    for (auto &element : _elements) {
        element->handleEvent(event, window);
    }
}

void UIBlocks::List::addElement(std::shared_ptr<IUIBlock> element)
{
    _elements.push_back(element);
}

void UIBlocks::List::removeElement(size_t index)
{
    if (index < _elements.size())
        _elements.erase(_elements.begin() + index);
}

void UIBlocks::List::setPosition(const std::pair<float, float> &position)
{
    _position = position;
    for (size_t i = 0; i < _elements.size(); ++i) {
        _elements[i]->setPosition(std::pair<float, float>(position.first, position.second + i * 20));
    }
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::List::getValue() const
{
    static std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> value = this->_elements;
    return value;
}

void UIBlocks::List::setSize(const std::pair<float, float> &size)
{
    _size = size;
    _background.setSize(sf::Vector2f(size.first, size.second));
    for (size_t i = 0; i < _elements.size(); ++i) {
        _elements[i]->setSize(size);
    }
}

void UIBlocks::List::setSize(const int size)
{
    for (size_t i = 0; i < _elements.size(); ++i) {
        _elements[i]->setSize(size);
    }
}
