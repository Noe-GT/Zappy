/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Timer
*/

#include "Timer.hpp"


UIBlocks::Timer::Timer(std::pair<float, float> position, int size): _text("0", position, size)
{
    this->_timer.restart();
}

void UIBlocks::Timer::draw(std::shared_ptr<zappyGUI::Window> &window)
{
    this->_text.setText(std::to_string(_timer.getElapsedTime().asSeconds()));
    this->_text.draw(window);
}

void UIBlocks::Timer::handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window)
{
    (void)event;
    (void)window;
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Timer::getValue() const
{
    static std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->_text.getValue();
    return value;
}

void UIBlocks::Timer::setPosition(const std::pair<float, float> &position)
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

void UIBlocks::Timer::setSize(const std::pair<float, float> &size)
{
    (void)size;
}

void UIBlocks::Timer::setSize(const int size)
{
    this->_text.setSize(size);
}