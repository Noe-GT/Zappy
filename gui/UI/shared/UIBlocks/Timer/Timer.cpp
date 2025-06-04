/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Timer
*/

#include "Timer.hpp"


UIBlocks::Timer::Timer(std::string font, std::pair<int, int> position, int size)
    : _text("0", font, position, size)
{
    this->_timer.restart();
}

void UIBlocks::Timer::draw(zappyGUI::Window &window)
{
    this->_text.setText(std::to_string(_timer.getElapsedTime().asSeconds()));
    this->_text.draw(window);
}

void UIBlocks::Timer::handleEvent(const sf::Event &event)
{
    (void)event;
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Timer::getValue() const
{
    static std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->_text.getValue();
    return value;
}

void UIBlocks::Timer::setPosition(const std::pair<int, int> &position)
{
    this->_text.setPosition(position);
}

void UIBlocks::Timer::start()
{
    this->_timer.restart();
    this->_text.setText(std::to_string(_timer.getElapsedTime().asSeconds()));
}

void UIBlocks::Timer::restart()
{
    this->_timer.restart();
}
