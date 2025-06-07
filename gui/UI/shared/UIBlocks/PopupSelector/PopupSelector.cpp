/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PopupSelector
*/

#include "PopupSelector.hpp"
#include <iostream>

const std::pair<float, float> PopupSelectorDefaultSize = std::pair<float, float>(200, 150);
const int PopupSelectorOptionsCharacterSize = 10;

UIBlocks::PopupSelector::PopupSelector(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> &options, std::pair<float, float> position):
    _position(position),
    _size(PopupSelectorDefaultSize),
    _options(options),
    _background(sf::Vector2f(_size.first, _size.second)),
    _selected(nullptr),
    _isOpen(false)
{
    for (auto &option : options)
        option.get()->setSize(PopupSelectorOptionsCharacterSize);
}

void UIBlocks::PopupSelector::draw(zappyGUI::Window &window)
{
    if (!_isOpen)
        return;
    this->_background.setPosition(this->_position.first, this->_position.second);
    this->_background.setSize(sf::Vector2f(this->_size.first, this->_size.second));
    this->_background.setOutlineColor(this->_borderColor);
    this->_background.setOutlineThickness(this->_borderThickness);
    this->_background.setFillColor(this->_backgroundColor);
    window.getRenderWindow().draw(this->_background);

    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> visibleOptions = this->_options.getVisibleOptions();
    for (size_t i = 0; i < visibleOptions.size(); ++i) {
        visibleOptions[i].get()->setPosition(std::pair<float, float>(this->_position.first + 10, this->_position.second + 10 + i * 30));
        visibleOptions[i]->draw(window);
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


void UIBlocks::PopupSelector::handleEvent(const sf::Event &event, zappyGUI::Window &window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window.getRenderWindow());
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isInside(event.mouseButton.x, event.mouseButton.y)) {
                int index = (event.mouseButton.y - _position.second) / 30;
                if (index >= 0 and index < (int)this->_options.getVisibleOptions().size()) {
                    this->_selected = this->_options.getVisibleOptions()[index];
                    std::cout << "Selected option: " << std::get<std::string>(this->_selected->getValue()) << std::endl;
                }
            }
        }
    } else if (isInside(mousePosition.x, mousePosition.y)) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0)
                this->_options.scrollUp();
            if (event.mouseWheelScroll.delta < 0)
                this->_options.scrollDown();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                this->_options.scrollUp();
            } else if (event.key.code == sf::Keyboard::Down) {
                this->_options.scrollDown();
            }
        }
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

void UIBlocks::PopupSelector::setSize(const std::pair<float, float> &size)
{
    this->_size = size;
    this->_background.setSize(sf::Vector2f(size.first, size.second));
}

void UIBlocks::PopupSelector::setSize(const int size)
{
    (void)size;
}