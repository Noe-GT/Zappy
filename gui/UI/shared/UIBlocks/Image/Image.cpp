/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Image
*/

#include "Image.hpp"

UIBlocks::Image::Image(const std::string &path, std::pair<int, int> position, std::pair<int, int> size, std::string &alternativeText):
    _alternativeText(alternativeText)
{
    this->_image.loadFromFile(path);
    this->_texture.loadFromImage(this->_image);
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(static_cast<float>(position.first), static_cast<float>(position.second));
    this->_sprite.setScale(static_cast<float>(size.first) / this->_image.getSize().x,
                           static_cast<float>(size.second) / this->_image.getSize().y);
}


void UIBlocks::Image::draw(zappyGUI::Window &window)
{
    window.getRenderWindow().draw(this->_sprite);
}

void UIBlocks::Image::setPosition(const std::pair<int, int> &position)
{
    this->_sprite.setPosition(static_cast<float>(position.first), static_cast<float>(position.second));
}

void UIBlocks::Image::handleEvent(const sf::Event &event)
{
    (void)event;
}

const std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> UIBlocks::Image::getValue() const
{
    std::variant<std::string, std::vector<std::shared_ptr<UIBlocks::IUIBlock>>> value = this->_alternativeText;
    return value;
}