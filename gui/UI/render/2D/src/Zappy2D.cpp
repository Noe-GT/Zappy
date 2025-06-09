/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy2D.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D():
    _tiles()
{
}

void zappyGUI::Zappy2D::initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize)
{
    zappyGUI::AGraphical::initialize(window, mapSize);
    for (size_t y = 0; y < mapSize.second; y++) {
        this->_tiles.emplace_back();
        for (size_t x = 0; x < mapSize.first; x++)
            this->_tiles.back().emplace_back(x, y);
    }
}

void zappyGUI::Zappy2D::display()
{
    // for (const std::vector<zappyGUI::Zappy2D::RTile> &tileRow : this->_tiles) {
    //     for (const zappyGUI::Zappy2D::RTile &tile : tileRow)
    //         tile.display(this->_window);
    // }
}

void zappyGUI::Zappy2D::update()
{
}

// void zappyGUI::Zappy2D::handleEvents()
// {
// }

void zappyGUI::Zappy2D::displayTile(const zappyGUI::Tile &tile) {
    this->_tiles[tile.getPos().second][tile.getPos().first].display(this->_window);
}

zappyGUI::Zappy2D::RTile::RTile(int x, int y)
{
    this->_back.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    this->_back.setFillColor(sf::Color::White);
    this->_back.setOutlineThickness(2);
    this->_back.setOutlineColor(sf::Color::Red);
    this->_back.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window) const
{
    window->getRenderWindow().draw(this->_back);
    for (const sf::CircleShape &player : this->_players)
        window->getRenderWindow().draw(player);
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    (void)tile;
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}
