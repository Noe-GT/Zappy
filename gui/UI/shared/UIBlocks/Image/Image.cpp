/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Image
*/

#include "Image.hpp"

UIBlocks::Image::Image(const std::string &path, std::pair<float, float> position, std::pair<float, float> size, std::string &alternativeText):
    _position(position), _size(size), _alternativeText(UIBlocks::Popup(alternativeText, position, size))
{
    this->_image.loadFromFile(path);
    this->_texture.loadFromImage(this->_image);
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(position.first, position.second);
    this->_sprite.setScale(size.first / this->_image.getSize().x,
                           size.second / this->_image.getSize().y);
}


void UIBlocks::Image::draw(zappyGUI::Window &window)
{
    this->_alternativeText.draw(window);
    window.getRenderWindow().draw(this->_sprite);
}

void UIBlocks::Image::setPosition(const std::pair<float, float> &position)
{
    this->_sprite.setPosition(position.first, position.second);
}

bool UIBlocks::Image::isInside(int x, int y) const
{
    return (x >= this->_position.first and x <= this->_position.first + _size.first and
            y >= this->_position.second and y <= this->_position.second + _size.second);
}


void UIBlocks::Image::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved) {
        if (this->isInside(event.mouseMove.x, event.mouseMove.y)) {
            this->_alternativeText.open();
        } else {
            this->_alternativeText.close();
        }
    }
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Image::getValue() const
{
    std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->_alternativeText.getValue();
    return value;
}