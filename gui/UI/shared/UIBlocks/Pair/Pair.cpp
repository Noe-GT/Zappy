/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Pair
*/

#include "Pair.hpp"

UIBlocks::Pair::Pair(std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>> &pair, std::pair<float, float> position):
    _pair(pair),
    _size(200, 50),
    _background(sf::Vector2f(_size.first, _size.second))
{
    this->setPosition(position);
}

void UIBlocks::Pair::draw(std::shared_ptr<zappyGUI::Window> &window)
{
    this->_background.setPosition(this->_position.first, this->_position.second);
    this->_background.setSize(sf::Vector2f(this->_size.first, this->_size.second));
    this->_background.setOutlineColor(this->_borderColor);
    this->_background.setOutlineThickness(this->_borderThickness);
    this->_background.setFillColor(this->_backgroundColor);
    window.get()->getRenderWindow().draw(this->_background);
    
    this->_pair.first->draw(window);
    this->_pair.second->draw(window);
}

void UIBlocks::Pair::setPosition(const std::pair<float, float> &position)
{
    this->_position = position;
    
    float padding = 10.0f;
    this->_pair.first->setPosition(std::pair<float, float>(position.first + padding, position.second + padding));
    
    float rightPosition = position.first + _size.first - padding;
    this->_pair.second->setPosition(std::pair<float, float>(rightPosition, position.second + padding));
}

void UIBlocks::Pair::handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window)
{
    this->_pair.first->handleEvent(event, window);
    this->_pair.second->handleEvent(event, window);
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Pair::getValue() const
{
    std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = std::vector<std::shared_ptr<UIBlocks::IUIBlock>>{this->_pair.first, this->_pair.second};
    return value;
}

void UIBlocks::Pair::setSize(const std::pair<float, float> &size)
{
    this->_size = size;
    this->_background.setSize(sf::Vector2f(size.first, size.second));
    
    this->setPosition(this->_position);
}

void UIBlocks::Pair::setSize(const int size)
{
    this->_pair.first->setSize(size);
    this->_pair.second->setSize(size);
}

void UIBlocks::Pair::setFirst(std::shared_ptr<IUIBlock> newFirst)
{
    this->_pair.first = newFirst;
}

void UIBlocks::Pair::setSecond(std::shared_ptr<IUIBlock> newSecond)
{
    this->_pair.second = newSecond;
}
