/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy2D.cpp
*/


#include "Zappy2D.hpp"
#include <iostream>

zappyGUI::Zappy2D::Zappy2D():
    _tiles(),
    _zoomCoeff(1.0)
{
}

void zappyGUI::Zappy2D::initialize(std::shared_ptr<zappyGUI::GUI> GUI)
{
    zappyGUI::AGraphical::initialize(GUI);

    this->_GUI = GUI;
    double widthRatio = static_cast<double>(GUI->getWindow()->getSize().first) / (GUI->getGame()->getMapSize().first * BASE_TILE_SIZE);
    double heightRatio = static_cast<double>(GUI->getWindow()->getSize().second) / (GUI->getGame()->getMapSize().second * BASE_TILE_SIZE);
    this->_zoomCoeff = std::min(widthRatio, heightRatio);
    this->_zoomCoeff = std::max(this->_zoomCoeff, ZOOM_COEFF_MIN);
    this->_zoomCoeff = std::min(this->_zoomCoeff, ZOOM_COEFF_MAX);

    _tiles.resize(GUI->getGame()->getMapSize().second);
    for (size_t y = 0; y < GUI->getGame()->getMapSize().second; y++) {
        _tiles[y].reserve(GUI->getGame()->getMapSize().first);
        for (size_t x = 0; x < GUI->getGame()->getMapSize().first; x++)
            _tiles[y].emplace_back(x, y, _zoomCoeff);
    }
}

void zappyGUI::Zappy2D::handleEvents()
{
    if (this->_window->getEvent().key.code == sf::Keyboard::Add)
        updateZoom(false);
    else if (this->_window->getEvent().key.code == sf::Keyboard::Subtract)
        updateZoom(true);
}

std::vector<std::vector<zappyGUI::Zappy2D::RTile>> &zappyGUI::Zappy2D::getTiles()
{
    return this->_tiles;
}

zappyGUI::Zappy2D::RTile &zappyGUI::Zappy2D::getTile(int x, int y)
{
    return this->_tiles[x][y];
}


void zappyGUI::Zappy2D::update()
{
    auto mapSize = _GUI->getGame()->getMapSize();

    if (_tiles.size() != mapSize.first || (_tiles.size() > 0 && _tiles[0].size() != mapSize.second)) {
        _tiles.clear();
        _tiles.resize(mapSize.first);
        for (size_t y = 0; y < mapSize.first; y++) {
            _tiles[y].reserve(mapSize.second);
            for (size_t x = 0; x < mapSize.second; x++) {
                _tiles[y].emplace_back(x, y, _zoomCoeff);
            }
        }
    }

    for (size_t y = 0; y < _tiles.size(); y++) {
        for (size_t x = 0; x < _tiles[y].size(); x++)
            _tiles[y][x].update(_GUI->getGame()->getMap()[x][y]);
    }
}

void zappyGUI::Zappy2D::updateZoom(bool zoomOut)
{
    if (zoomOut && _zoomCoeff > ZOOM_COEFF_MIN) {
        _zoomCoeff -= ZOOM_COEFF_SENSITIVITY;
    } else if (!zoomOut && _zoomCoeff < ZOOM_COEFF_MAX) {
        _zoomCoeff += ZOOM_COEFF_SENSITIVITY;
    }

    for (auto& row : _tiles) {
        for (auto& tile : row) {
            tile.updateZoom(_zoomCoeff);
        }
    }
}

void zappyGUI::Zappy2D::display()
{
    if (_tiles.empty() || _tiles[0].empty())
        return;

    float totalWidth = _tiles[0].size() * BASE_TILE_SIZE * _zoomCoeff;
    float totalHeight = _tiles.size() * BASE_TILE_SIZE * _zoomCoeff;

    float offsetX = (_window->getSize().first - totalWidth) / 2;
    float offsetY = (_window->getSize().second - totalHeight) / 2;

    sf::View view = _window->getRenderWindow().getDefaultView();
    view.setCenter(totalWidth/2 + offsetX, totalHeight/2 + offsetY);
    _window->getRenderWindow().setView(view);

    for (auto& row : _tiles) {
        for (auto& tile : row) {
            tile.display(_window, offsetX, offsetY);
        }
    }
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window, float offsetX, float offsetY) const
{
    sf::RectangleShape tileBack = _back;
    tileBack.move(offsetX, offsetY);
    window->getRenderWindow().draw(tileBack);
    if (this->_players.size() != 0) {
        sf::CircleShape offsetPlayer = this->_players[0];
        offsetPlayer.setPosition(tileBack.getPosition());
        window->getRenderWindow().draw(offsetPlayer);
    }
}

void zappyGUI::Zappy2D::updateTile(const zappyGUI::Tile &tile)
{
    _tiles[tile.getPos().second][tile.getPos().first].update(tile);
}

zappyGUI::Zappy2D::RTile::RTile(int x, int y, double zoomCoeff):
    _zoomCoeff(zoomCoeff),
    _back(),
    _players()
{
    updateVisuals(x, y);
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    _players.clear();
    for (const std::shared_ptr<zappyGUI::Player> &player : tile.getPlayers()) {
        sf::CircleShape playerShape(BASE_PLAYER_SIZE * _zoomCoeff);
        playerShape.setFillColor(sf::Color::Green);
        playerShape.setPosition(
            _back.getPosition().x + (BASE_TILE_SIZE * _zoomCoeff)/2 - BASE_PLAYER_SIZE * _zoomCoeff,
            _back.getPosition().y + (BASE_TILE_SIZE * _zoomCoeff)/2 - BASE_PLAYER_SIZE * _zoomCoeff
        );
        _players.push_back(playerShape);
    }
}

void zappyGUI::Zappy2D::RTile::updateZoom(double newZoom)
{
    _zoomCoeff = newZoom;
    updateVisuals(_back.getPosition().x / (BASE_TILE_SIZE * _zoomCoeff),
                 _back.getPosition().y / (BASE_TILE_SIZE * _zoomCoeff));
}

void zappyGUI::Zappy2D::RTile::updateVisuals(int x, int y)
{
    this->_back.setSize(sf::Vector2f(BASE_TILE_SIZE * _zoomCoeff, BASE_TILE_SIZE * _zoomCoeff));
    this->_back.setFillColor(sf::Color::White);
    this->_back.setOutlineThickness(2 * _zoomCoeff);
    this->_back.setOutlineColor(sf::Color::Red);
    this->_back.setPosition(sf::Vector2f(
        x * (BASE_TILE_SIZE * _zoomCoeff),
        y * (BASE_TILE_SIZE * _zoomCoeff)
    ));
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}