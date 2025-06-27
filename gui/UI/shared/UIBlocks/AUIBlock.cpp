/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AUIBlock
*/

#include "AUIBlock.hpp"
#include <iostream>

UIBlocks::AUIBlock::AUIBlock()
    : _borderColor(sf::Color::White), _backgroundColor(sf::Color(50, 50, 50, 200)),
      _borderThickness(0), _textColor(sf::Color::White)
{
    if (!this->_font.loadFromFile("gui/UI/shared/UIBlocks/assets/fonts/Roboto.ttf"))
        std::cerr << "Failed to load font" << std::endl;
}

void UIBlocks::AUIBlock::draw(std::shared_ptr<zappyGUI::Window> &window)
{
    (void)window; 
}

void UIBlocks::AUIBlock::handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window)
{
    (void)event; 
    (void)window;
}

void UIBlocks::AUIBlock::setPosition(const std::pair<float, float> &position)
{
    (void)position; 
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::AUIBlock::getValue() const
{
    return std::string();
}

void UIBlocks::AUIBlock::setSize(const std::pair<float, float> &size)
{
    (void)size; 
}

void UIBlocks::AUIBlock::setSize(const int size)
{
    (void)size; 
}

