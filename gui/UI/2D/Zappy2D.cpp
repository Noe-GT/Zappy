/*
** EPITECH PROJECT, 2025
** zappy - gui
** File description:
** Zappy2D
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D(zappyGUI::Window &window, zappyGUI::Game &game):
    zappyGUI::AGraphical(window, game),
    _tiles(std::vector<std::vector<sf::RectangleShape>>(game.getMapSize().second, std::vector<sf::RectangleShape>(game.getMapSize().first)))
{
    size_t x = 0;
    size_t y = 0;

    for (std::vector<sf::RectangleShape> &tileLine : this->_tiles) {
        for (sf::RectangleShape &tile : tileLine) {
            tile.setSize(sf::Vector2f(50, 50));
            tile.setFillColor(sf::Color::White);
            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color::Red);
            tile.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
            x++;
        }
        y++;
        x = 0;
    }
}

void zappyGUI::Zappy2D::display()
{
    // std::vector<std::vector<zappyGUI::Tile>> &map = this->_game.getMap();
    // for (const std::vector<zappyGUI::Tile>& tileLine: this->_game.getMap()) {
    //     for (const zappyGUI::Tile &t : tileLine) {
    //         this->
    //     }
    // }
    this->_window.clear();
    for (const std::vector<sf::RectangleShape> &tileLine : this->_tiles) {
        for (const sf::RectangleShape &tile : tileLine) {
            this->_window.getRenderWindow().draw(tile);
        }
    }
}

void zappyGUI::Zappy2D::update()
{
}

void zappyGUI::Zappy2D::handleEvents()
{
}
