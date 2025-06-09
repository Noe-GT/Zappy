/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy2D.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D():
    _tiles(std::vector<std::vector<sf::RectangleShape>>(30, std::vector<sf::RectangleShape>(30)))
{
}

void zappyGUI::Zappy2D::initialize(std::shared_ptr<zappyGUI::Window> window, std::shared_ptr<zappyGUI::Game> game)
{
    size_t x = 0;
    size_t y = 0;

    zappyGUI::AGraphical::initialize(window, game);
    for (std::vector<sf::RectangleShape> &tileLine : this->_tiles) {
        for (sf::RectangleShape &tile : tileLine) {
            tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setFillColor(sf::Color::White);
            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color::Red);
            tile.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
            x++;
        }
        y++;
        x = 0;
    }
    printf("tiles: %ld\n", this->_tiles.size());

    // printf("tiles: %ld | gsize : %dx%d\n", this->_tiles.size(), game->getMapSize().first, game->getMapSize().second);
    // game->display();
}

void zappyGUI::Zappy2D::display()
{
    // std::vector<std::vector<zappyGUI::Tile>> &map = this->_game.getMap();
    // for (const std::vector<zappyGUI::Tile>& tileLine: this->_game.getMap()) {
    //     for (const zappyGUI::Tile &t : tileLine) {
    //         this->
    //     }
    // }
    for (const std::vector<sf::RectangleShape> &tileLine : this->_tiles) {
        for (const sf::RectangleShape &tile : tileLine) {
            this->_window->getRenderWindow().draw(tile);
        }
    }
}

void zappyGUI::Zappy2D::update()
{
}

// void zappyGUI::Zappy2D::handleEvents()
// {
// }

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}
