/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Pair
*/

#include "Pair.hpp"

UIBlocks::Pair::Pair(std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>> &pair, std::pair<int, int> position):
    _pair(pair)
{
    this->setPosition(position);
}

void UIBlocks::Pair::draw(zappyGUI::Window &window)
{
    this->_pair.first->draw(window);
    this->_pair.second->draw(window);
}

void UIBlocks::Pair::setPosition(const std::pair<int, int> &position)
{
    this->_position = position;
    this->_pair.first->setPosition(position);
    this->_pair.second->setPosition(std::pair<int, int>(position.first + 20, position.second));
}

void UIBlocks::Pair::handleEvent(const sf::Event &event)
{
    this->_pair.first->handleEvent(event);
    this->_pair.second->handleEvent(event);
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Pair::getValue() const
{
    static std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = std::vector<std::shared_ptr<UIBlocks::IUIBlock>>{this->_pair.first, this->_pair.second};
    return value;
}

