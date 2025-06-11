/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Rtile.cpp
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
    for (const std::shared_ptr<zappyGUI::Player> &player : tile.getPlayers()) {
        sf::CircleShape playerShape(BASE_PLAYER_SIZE * this->_zoomCoeff);
        playerShape.setFillColor(sf::Color::Green);
        playerShape.setPosition(
            this->_back.getPosition().x + (BASE_TILE_SIZE * this->_zoomCoeff) / 2 - BASE_PLAYER_SIZE * this->_zoomCoeff,
            this->_back.getPosition().y + (BASE_TILE_SIZE * this->_zoomCoeff) / 2 - BASE_PLAYER_SIZE * this->_zoomCoeff
        );
        this->_players.push_back(playerShape);
    }
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window, float offsetX, float offsetY) const
{
    sf::RectangleShape tileBack = this->_back;
    tileBack.move(offsetX, offsetY);
    window->getRenderWindow().draw(tileBack);
    if (this->_players.size() != 0) {
        sf::CircleShape offsetPlayer = this->_players[0];
        offsetPlayer.setPosition(tileBack.getPosition());
        window->getRenderWindow().draw(offsetPlayer);
    }
}

void zappyGUI::Zappy2D::RTile::updateZoom(double newZoom)
{
    this->_zoomCoeff = newZoom;
    updateVisuals(_back.getPosition().x / (BASE_TILE_SIZE * this->_zoomCoeff), _back.getPosition().y / (BASE_TILE_SIZE * this->_zoomCoeff));
}

void zappyGUI::Zappy2D::RTile::updateVisuals(int x, int y)
{
    this->_back.setSize(sf::Vector2f(BASE_TILE_SIZE * this->_zoomCoeff, BASE_TILE_SIZE * this->_zoomCoeff));
    this->_back.setFillColor(sf::Color::White);
    this->_back.setOutlineThickness(2 * this->_zoomCoeff);
    this->_back.setOutlineColor(sf::Color::Red);
    this->_back.setPosition(sf::Vector2f(x * (BASE_TILE_SIZE * this->_zoomCoeff),y * (BASE_TILE_SIZE * this->_zoomCoeff)));
}
