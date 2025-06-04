/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PopupSelector
*/

#include "PopupSelector.hpp"

UIBlocks::PopupSelector::PopupSelector(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> &options, std::pair<float, float> position, std::pair<float, float> size):
    _position(position),
    _size(size),
    _options(options),
    _background(sf::Vector2f(_size.first, _size.second)),
    _selected(nullptr),
    _isOpen(false)
{
}

void UIBlocks::PopupSelector::draw(zappyGUI::Window &window)
{
    if (!_isOpen)
        return;
    this->_background.setPosition(this->_position.first, this->_position.second);
    this->_background.setFillColor(sf::Color(50, 50, 50, 200));
    window.getRenderWindow().draw(_background);

    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> visibleOptions = this->_options.getVisibleOptions();
    for (size_t i = 0; i < visibleOptions.size(); ++i) {
        sf::Text optionText;
        visibleOptions[i].get()->setPosition(std::pair<float, float>(this->_position.first + 10, this->_position.second + 10 + i * 30));
        optionText.setFillColor(sf::Color::White);
        window.getRenderWindow().draw(optionText);
    }
}

void UIBlocks::PopupSelector::open()
{
    this->_isOpen = true;
}

void UIBlocks::PopupSelector::close()
{
    this->_isOpen = false;
}

const std::shared_ptr<UIBlocks::IUIBlock> &UIBlocks::PopupSelector::getSelected() const
{
    return _selected;
}

bool UIBlocks::PopupSelector::isInside(int x, int y) const
{
    return (x >= this->_position.first and x <= this->_position.first + _size.first and
            y >= this->_position.second and y <= this->_position.second + _size.second);
}


void UIBlocks::PopupSelector::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isInside(event.mouseButton.x, event.mouseButton.y)) {
                int index = (event.mouseButton.y - _position.second) / 30;
                if (index >= 0 and index < (int)this->_options.getVisibleOptions().size()) 
                    this->_selected = this->_options.getVisibleOptions()[index];
            }
        }
    } else if (isInside(event.mouseButton.x, event.mouseButton.y) and event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            this->_options.scrollUp();
        else
            this->_options.scrollDown();
    }
}

void UIBlocks::PopupSelector::setPosition(const std::pair<float, float> &position)
{
    this->_position = position;
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::PopupSelector::getValue() const
{
    std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->getSelected().get()->getValue();
    return value;
}

