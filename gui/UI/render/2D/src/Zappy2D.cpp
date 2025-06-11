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
    _zoomCoeff(1.0),
    _mapOffsetX(0.0f),
    _mapOffsetY(0.0f)
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
    computeMapOffsets();
}

void zappyGUI::Zappy2D::computeZoom()
{
    std::pair<size_t, size_t> mapSize = _GUI->getGame()->getMapSize();
    if (mapSize.first == 0 || mapSize.second == 0)
        return;
    double windowWidth = static_cast<double>(_window->getSize().first);
    double windowHeight = static_cast<double>(_window->getSize().second);
    double availableWidth = windowWidth * (1.0 - 2 * MARGIN_HORIZONTAL_RATIO);
    double availableHeight = windowHeight - (2 * MARGIN_VERTICAL);
    availableHeight = std::max(availableHeight, 1.0);
    double widthRatio = availableWidth / (mapSize.first * BASE_TILE_SIZE);
    double heightRatio = availableHeight / (mapSize.second * BASE_TILE_SIZE);
    this->_zoomCoeff = std::min(widthRatio, heightRatio);
    this->_zoomCoeff = std::max(std::min(this->_zoomCoeff, ZOOM_COEFF_MAX), ZOOM_COEFF_MIN);
    std::clog << _zoomCoeff << std::endl;
}

void zappyGUI::Zappy2D::computeMapOffsets()
{
    if (!_GUI || _tiles.empty() || _tiles[0].empty())
        return;

    auto mapSize = _GUI->getGame()->getMapSize();
    float totalMapWidth = mapSize.first * BASE_TILE_SIZE * this->_zoomCoeff;
    float totalMapHeight = mapSize.second * BASE_TILE_SIZE * this->_zoomCoeff;
    this->_mapOffsetX = (_window->getSize().first - totalMapWidth) / 2;
    float availableVerticalSpace = _window->getSize().second - (2 * MARGIN_VERTICAL);
    this->_mapOffsetY = MARGIN_VERTICAL + (availableVerticalSpace - totalMapHeight) / 2;
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
    if (_tiles.size() != mapSize.second || (_tiles.size() > 0 && this->_tiles[0].size() != mapSize.first)) {
        computeZoom();
        this->_tiles.clear();
        this->_tiles.resize(mapSize.second);
        for (size_t y = 0; y < mapSize.second; y++) {
            this->_tiles[y].reserve(mapSize.first);
            for (size_t x = 0; x < mapSize.first; x++) {
                this->_tiles[y].emplace_back(x, y, this->_zoomCoeff);
            }
        }
        computeMapOffsets();
    }
    const auto& gameMap = _GUI->getGame()->getMap();
    if (gameMap.size() != mapSize.first || (gameMap.size() > 0 && gameMap[0].size() != mapSize.second)) {
        return;
    }

    for (size_t y = 0; y < this->_tiles.size() && y < mapSize.second; y++) {
        for (size_t x = 0; x < this->_tiles[y].size() && x < mapSize.first; x++) {
            if (x < gameMap.size() && y < gameMap[x].size()) {
                this->_tiles[y][x].update(gameMap[x][y]);
            }
        }
    }
}

void zappyGUI::Zappy2D::updateZoom(bool zoomOut)
{
    double oldZoom = this->_zoomCoeff;

    if (zoomOut && this->_zoomCoeff > ZOOM_COEFF_MIN)
        this->_zoomCoeff -= ZOOM_COEFF_SENSITIVITY;
    if (!zoomOut && this->_zoomCoeff < ZOOM_COEFF_MAX)
        this->_zoomCoeff += ZOOM_COEFF_SENSITIVITY;

    std::pair<size_t, size_t> mapSize = _GUI->getGame()->getMapSize();
    double windowWidth = static_cast<double>(_window->getSize().first);
    double windowHeight = static_cast<double>(_window->getSize().second);
    double availableWidth = windowWidth * (1.0 - 2 * MARGIN_HORIZONTAL_RATIO);
    double availableHeight = windowHeight - (2 * MARGIN_VERTICAL);
    double requiredWidth = mapSize.first * BASE_TILE_SIZE * _zoomCoeff;
    double requiredHeight = mapSize.second * BASE_TILE_SIZE * _zoomCoeff;
    if (requiredWidth > availableWidth || requiredHeight > availableHeight) {
        computeZoom();
    }
    if (oldZoom != this->_zoomCoeff) {
        for (auto& row : this->_tiles) {
            for (auto& tile : row)
                tile.updateZoom(_zoomCoeff);
        }
        computeMapOffsets();
    }
}

void zappyGUI::Zappy2D::display()
{
    if (_tiles.empty() || this->_tiles[0].empty())
        return;
    computeMapOffsets();
    for (auto& row : this->_tiles) {
        for (auto& tile : row) {
            tile.display(_window, _mapOffsetX, _mapOffsetY);
        }
    }
}

void zappyGUI::Zappy2D::updateTile(const zappyGUI::Tile &tile)
{
    auto pos = tile.getPos();

    if (pos.second < _tiles.size() && pos.first < _tiles[pos.second].size()) {
        this->_tiles[pos.second][pos.first].update(tile);
    }
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}
