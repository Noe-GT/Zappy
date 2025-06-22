/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Image
*/

#include "Image.hpp"
#include <iostream>

UIBlocks::Image::Image(const std::string &path, std::pair<float, float> position, std::pair<float, float> size, std::string &alternativeText):
    _position(position), _size(size), _alternativeText(UIBlocks::Popup(alternativeText, position, size))
{
    this->_image.loadFromFile(path);
    this->_texture.create(size.first, size.second);
    if (!this->_texture.loadFromFile(path))
        std::cerr << "Error loading image from path: " << path << std::endl;
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(position.first, position.second);
    this->_sprite.setScale(size.first / this->_image.getSize().x,
                           size.second / this->_image.getSize().y);
}


void UIBlocks::Image::draw(std::shared_ptr<zappyGUI::Window> &window)
{
    this->_sprite.setPosition(this->_position.first, this->_position.second);
    this->_sprite.setScale(this->_size.first / this->_image.getSize().x,
                           this->_size.second / this->_image.getSize().y);
    this->_sprite.setTexture(this->_texture);
    window.get()->getRenderWindow().draw(this->_sprite);
    this->_alternativeText.draw(window);
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


void UIBlocks::Image::handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window)
{
    (void)window;
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

void UIBlocks::Image::setSize(const std::pair<float, float> &size)
{
    this->_size = size;
    this->_sprite.setScale(size.first / this->_image.getSize().x,
                           size.second / this->_image.getSize().y);
}

void UIBlocks::Image::setSize(const int size)
{
    this->_size = std::pair<float, float>(size, size);
    this->_sprite.setScale(size / this->_image.getSize().x,
                           size / this->_image.getSize().y);
    this->_alternativeText.setSize(size);
}