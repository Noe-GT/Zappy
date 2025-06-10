/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PopupSelector
*/

#include "PopupSelector.hpp"
#include <iostream>

const std::pair<float, float> PopupSelectorDefaultSize = std::pair<float, float>(200, 150);
const int OPTION_CHARACTER_SIZE = 20;
const int OPTION_HORIZONTAL_SPACING = 10;
const float OPTION_VERTICAL_SPACING = OPTION_CHARACTER_SIZE * 1.5f;
const int OPTION_HEIGHT = OPTION_CHARACTER_SIZE + OPTION_VERTICAL_SPACING;


UIBlocks::PopupSelector::PopupSelector(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> &options, std::pair<float, float> position):
    _position(position),
    _size(PopupSelectorDefaultSize),
    _options(options),
    _background(sf::Vector2f(_size.first, _size.second)),
    _selected(nullptr),
    _isOpen(false)
{
    for (auto &option : options)
        option.get()->setSize(OPTION_CHARACTER_SIZE);
    updateMaxVisibleOptions();
}

UIBlocks::PopupSelector::PopupSelector(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> &options, std::pair<float, float> position, std::pair<float, float> size):
    _position(position),
    _size(size),
    _options(options),
    _background(sf::Vector2f(_size.first, _size.second)),
    _selected(nullptr),
    _isOpen(false)
{
    for (auto &option : options)
        option.get()->setSize(OPTION_CHARACTER_SIZE);
    updateMaxVisibleOptions();
}


void UIBlocks::PopupSelector::updateMaxVisibleOptions()
{
    float availableHeight = _size.second - (2 * OPTION_HORIZONTAL_SPACING);
    int maxOptions = static_cast<int>(availableHeight / OPTION_VERTICAL_SPACING);
    maxOptions = std::max(1, maxOptions);
    _options.setMaxVisibleOptions(maxOptions);
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
        visibleOptions[i].get()->setPosition(std::pair<float, float>(this->_position.first + OPTION_HORIZONTAL_SPACING, this->_position.second + OPTION_HORIZONTAL_SPACING + i * OPTION_VERTICAL_SPACING));
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
                int index = (event.mouseButton.y - _position.second - OPTION_HORIZONTAL_SPACING) / OPTION_VERTICAL_SPACING;
                auto visibleOptions = this->_options.getVisibleOptions();
                if (index >= 0 && index < static_cast<int>(visibleOptions.size())) {
                    std::cout << "Clicked on option index: " << index << std::endl;
                    this->_selected = visibleOptions[index];
                    std::cout << "Selected option: " << std::get<std::string>(std::get<std::vector<std::shared_ptr<UIBlocks::IUIBlock>>>(this->_selected->getValue()).at(1).get()->getValue()) << std::endl;
                }
            }
        }
    }
    else if (isInside(mousePosition.x, mousePosition.y)) {
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