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
    computeZoom();
    this->_tiles.resize(GUI->getGame()->getMapSize().second);
    for (size_t y = 0; y < GUI->getGame()->getMapSize().second; y++) {
        this->_tiles[y].reserve(GUI->getGame()->getMapSize().first);
        for (size_t x = 0; x < GUI->getGame()->getMapSize().first; x++)
            this->_tiles[y].emplace_back(x, y, this->_zoomCoeff);
    }
}

void zappyGUI::Zappy2D::computeZoom()
{
    std::pair<size_t, size_t> mapSize = _GUI->getGame()->getMapSize();
    if (mapSize.first == 0 || mapSize.second == 0)
        return;
    double availableHeight = static_cast<double>(_window->getSize().second) - (2 * MARGIN);
    availableHeight = std::max(availableHeight, 1.0);
    double widthRatio = static_cast<double>(_window->getSize().first) / (mapSize.first * BASE_TILE_SIZE);
    double heightRatio = availableHeight / (mapSize.second * BASE_TILE_SIZE);
    this->_zoomCoeff = std::min(widthRatio, heightRatio);
    this->_zoomCoeff = std::max(std::min(this->_zoomCoeff, ZOOM_COEFF_MAX), ZOOM_COEFF_MIN);
}

void zappyGUI::Zappy2D::handleEvents()
{
    //TODO: handle mouse event to draw popup
}

std::vector<std::vector<zappyGUI::Zappy2D::RTile>> &zappyGUI::Zappy2D::getTiles()
{
    return this->_tiles;
}

zappyGUI::Zappy2D::RTile &zappyGUI::Zappy2D::getTile(int x, int y)
{
    return this->_tiles[y][x];
}

void zappyGUI::Zappy2D::update()
{
    auto mapSize = this->_GUI->getGame()->getMapSize();

    if (_tiles.size() != mapSize.first || (_tiles.size() > 0 && this->_tiles[0].size() != mapSize.second)) {
        computeZoom();
        this->_tiles.clear();
        this->_tiles.resize(mapSize.first);
        for (size_t y = 0; y < mapSize.first; y++) {
            this->_tiles[y].reserve(mapSize.second);
            for (size_t x = 0; x < mapSize.second; x++) {
                this->_tiles[y].emplace_back(x, y, this->_zoomCoeff);
            }
        }
    }

    for (size_t y = 0; y < this->_tiles.size(); y++) {
        for (size_t x = 0; x < this->_tiles[y].size(); x++)
            this->_tiles[y][x].update(_GUI->getGame()->getMap()[x][y]);
    }
}

void zappyGUI::Zappy2D::updateZoom(bool zoomOut)
{
    if (zoomOut && this->_zoomCoeff > ZOOM_COEFF_MIN)
        this->_zoomCoeff -= ZOOM_COEFF_SENSITIVITY;
    if (!zoomOut && this->_zoomCoeff < ZOOM_COEFF_MAX)
        this->_zoomCoeff += ZOOM_COEFF_SENSITIVITY;
    auto mapSize = _GUI->getGame()->getMapSize();
    double requiredWidth = mapSize.first * BASE_TILE_SIZE * _zoomCoeff;
    double requiredHeight = mapSize.second * BASE_TILE_SIZE * _zoomCoeff;

    if (requiredWidth > _window->getSize().first || requiredHeight > _window->getSize().second)
        computeZoom();
    for (auto& row : this->_tiles) {
        for (auto& tile : row)
            tile.updateZoom(_zoomCoeff);
    }
}

void zappyGUI::Zappy2D::display()
{
    if (_tiles.empty() || this->_tiles[0].empty())
        return;

    float totalWidth = this->_tiles[0].size() * BASE_TILE_SIZE * this->_zoomCoeff;
    float totalHeight = this->_tiles.size() * BASE_TILE_SIZE * this->_zoomCoeff;
    float offsetX = (_window->getSize().first - totalWidth) / 2;
    float offsetY = MARGIN;
    if (totalHeight < (_window->getSize().second - 2 * MARGIN))
        offsetY += (_window->getSize().second - 2 * MARGIN - totalHeight) / 2;
    sf::View view = this->_window->getRenderWindow().getDefaultView();
    view.setCenter(totalWidth/2 + offsetX, totalHeight/2 + offsetY);
    this->_window->getRenderWindow().setView(view);

    for (auto& row : this->_tiles) {
        for (auto& tile : row) {
            tile.display(_window, offsetX, offsetY);
        }
    }
}

void zappyGUI::Zappy2D::updateTile(const zappyGUI::Tile &tile)
{
    this->_tiles[tile.getPos().second][tile.getPos().first].update(tile);
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}