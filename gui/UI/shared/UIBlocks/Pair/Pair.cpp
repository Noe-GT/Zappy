/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Pair
*/

#include "Pair.hpp"

UIBlocks::Pair::Pair(std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>> &pair, std::pair<float, float> position):
    _pair(pair)
{
    this->setPosition(position);
}

void UIBlocks::Pair::draw(zappyGUI::Window &window)
{
    this->_pair.first->draw(window);
    this->_pair.second->draw(window);
}

void UIBlocks::Pair::setPosition(const std::pair<float, float> &position)
{
    this->_position = position;
    this->_pair.first->setPosition(position);
    this->_pair.second->setPosition(std::pair<float, float>(position.first + 20, position.second));
}

void UIBlocks::Pair::handleEvent(const sf::Event &event, zappyGUI::Window &window)
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
    this->_pair.first->setSize(size);
    this->_pair.second->setSize(size);
}

void UIBlocks::Pair::setSize(const int size)
{
    this->_pair.first->setSize(size);
    this->_pair.second->setSize(size);
}

