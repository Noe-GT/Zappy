/*
** EPITECH PROJECT, 2024
** zap
** File description:
** RTile.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::RTile::RTile(int x, int y, double zoomCoeff):
    _zoomCoeff(zoomCoeff),
    _back(),
    _players()
{
    updateVisuals(x, y);
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    this->_players.clear();

    try {
        const auto& players = tile.getPlayers();
        this->_players.reserve(players.size());
        for (const std::shared_ptr<zappyGUI::Player> &player : players) {
            if (!player) {
                continue;
            }
            sf::CircleShape playerShape(BASE_PLAYER_SIZE * this->_zoomCoeff);
            playerShape.setFillColor(sf::Color::Green);
            float playerX = this->_back.getPosition().x + (BASE_TILE_SIZE * this->_zoomCoeff) / 2 - (BASE_PLAYER_SIZE * this->_zoomCoeff);
            float playerY = this->_back.getPosition().y + (BASE_TILE_SIZE * this->_zoomCoeff) / 2 - (BASE_PLAYER_SIZE * this->_zoomCoeff);
            playerShape.setPosition(playerX, playerY);
            this->_players.push_back(playerShape);
        }
    } catch (const std::exception& e) {
        this->_players.clear();
    }
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window, float offsetX, float offsetY) const
{
    sf::RectangleShape tileBack = this->_back;
    tileBack.move(offsetX, offsetY);
    window->getRenderWindow().draw(tileBack);

    for (const auto& player : this->_players) {
        sf::CircleShape offsetPlayer = player;
        offsetPlayer.move(offsetX, offsetY);
        window->getRenderWindow().draw(offsetPlayer);
    }
}

void zappyGUI::Zappy2D::RTile::updateZoom(double newZoom)
{
    if (newZoom == this->_zoomCoeff)
        return;
    int x = static_cast<int>(this->_back.getPosition().x / (BASE_TILE_SIZE * this->_zoomCoeff));
    int y = static_cast<int>(this->_back.getPosition().y / (BASE_TILE_SIZE * this->_zoomCoeff));

    this->_zoomCoeff = newZoom;
    updateVisuals(x, y);
}

void zappyGUI::Zappy2D::RTile::updateVisuals(int x, int y)
{
    float tileSize = BASE_TILE_SIZE * this->_zoomCoeff;

    this->_back.setSize(sf::Vector2f(tileSize, tileSize));
    this->_back.setFillColor(sf::Color::White);
    this->_back.setOutlineThickness(2 * this->_zoomCoeff);
    this->_back.setOutlineColor(sf::Color::Red);

    this->_back.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
}