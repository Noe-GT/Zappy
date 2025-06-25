/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy2D.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D():
    _assets(),
    _tiles(),
    _zoomCoeff(1.0),
    _mapOffset(std::pair<float, float>(200.00, 20.0)),
    _displayRessourceType(zappyGUI::Zappy2D::FOOD)
{
}

void zappyGUI::Zappy2D::initialize(std::shared_ptr<zappyGUI::GUI> gui)
{
    const std::pair<size_t, size_t> &mapSize = gui->getGame()->getMapSize();

    zappyGUI::AGraphical::initialize(gui);
    this->zoomFill();
    for (size_t y = 0; y < mapSize.second; y++) {
        this->_tiles.emplace_back();
        for (size_t x = 0; x < mapSize.first; x++)
            this->_tiles.back().emplace_back(x, y, std::shared_ptr<zappyGUI::Zappy2D>(this));
    }
    this->centerMap();
}

void zappyGUI::Zappy2D::zoomFill()
{
    const std::pair<size_t, size_t> &mapSize = this->_gui->getGame()->getMapSize();
    float windowWidth = this->_window->getSize().first;
    float windowHeight = this->_window->getSize().second;
    float widthRatio;
    float heightRatio;

    if (mapSize.first == 0 || mapSize.second == 0)
        return;
    if (windowHeight < 1.0)
        windowHeight = 1.0;
    widthRatio = windowWidth / (mapSize.first * zappyGUI::BASE_TILE_SIZE);
    heightRatio = windowHeight / (mapSize.second * zappyGUI::BASE_TILE_SIZE);
    this->_zoomCoeff = std::min(widthRatio, heightRatio);
    this->_zoomCoeff = std::max(std::min(this->_zoomCoeff, zappyGUI::ZOOM_COEFF_MAX), zappyGUI::ZOOM_COEFF_MIN);
}

void zappyGUI::Zappy2D::centerMap()
{
    const std::pair<size_t, size_t> &mapSize = this->_gui->getGame()->getMapSize();

    this->_mapOffset.first = (this->_window->getSize().first - (mapSize.first * zappyGUI::BASE_TILE_SIZE * this->_zoomCoeff)) / 2.0;
    this->_mapOffset.second = (this->_window->getSize().second - (mapSize.second * zappyGUI::BASE_TILE_SIZE * this->_zoomCoeff)) / 2.0;
}

void zappyGUI::Zappy2D::updateZoom(bool zoomOut)
{
    if (zoomOut && this->_zoomCoeff > zappyGUI::ZOOM_COEFF_MIN) {
        this->_zoomCoeff -= zappyGUI::ZOOM_COEFF_SENSITIVITY;
    } else if (!zoomOut && this->_zoomCoeff < zappyGUI::ZOOM_COEFF_MAX) {
        this->_zoomCoeff += zappyGUI::ZOOM_COEFF_SENSITIVITY;
    }
}

void zappyGUI::Zappy2D::updatePosition(sf::Keyboard::Key eventCode)
{
    if (eventCode == sf::Keyboard::Right) {
        (this->_mapOffset).first += zappyGUI::MAP_OFFSET_SENSITIVITY * (this->_zoomCoeff);
    } else if (eventCode == sf::Keyboard::Left) {
        (this->_mapOffset).first -= zappyGUI::MAP_OFFSET_SENSITIVITY * (this->_zoomCoeff);
    } else if (eventCode == sf::Keyboard::Up) {
        (this->_mapOffset).second -= zappyGUI::MAP_OFFSET_SENSITIVITY * (this->_zoomCoeff);
    } else if (eventCode == sf::Keyboard::Down) {
        (this->_mapOffset).second += zappyGUI::MAP_OFFSET_SENSITIVITY * (this->_zoomCoeff);
    }
}

void zappyGUI::Zappy2D::display()
{
}

void zappyGUI::Zappy2D::update()
{
}

void zappyGUI::Zappy2D::updateTile(const zappyGUI::Tile &tile) {
    this->_tiles[tile.getPos().second][tile.getPos().first].update(tile);
}

void zappyGUI::Zappy2D::displayTile(const zappyGUI::Tile &tile) {
    this->_tiles[tile.getPos().second][tile.getPos().first].display(this->_window);
}

const std::string &zappyGUI::Zappy2D::getDisplayTeam() const
{
    return this->_displayTeam;
}

const float &zappyGUI::Zappy2D::getZoomCoeff() const
{
    return this->_zoomCoeff;
}

const std::pair<float, float> &zappyGUI::Zappy2D::getMapOffset() const
{
    return this->_mapOffset;
}

const zappyGUI::Zappy2D::ressourceType &zappyGUI::Zappy2D::getDisplayRessourceType() const
{
    return this->_displayRessourceType;
}

const zappyGUI::Zappy2D::AssetPool &zappyGUI::Zappy2D::getAssets() const
{
    return this->_assets;
}

void zappyGUI::Zappy2D::handleEvents()
{
    sf::Keyboard::Key eventCode = this->_window->getEvent().key.code;

    switch (eventCode) {
        case sf::Keyboard::C:
            this->zoomFill();
            this->centerMap();
            break;
        case sf::Keyboard::Add:
            this->updateZoom(false);
            break;
        case sf::Keyboard::Subtract:
            this->updateZoom(true);
            break;
        case sf::Keyboard::Left:
            this->updatePosition(eventCode);
            break;
        case sf::Keyboard::Right:
            this->updatePosition(eventCode);
            break;
        case sf::Keyboard::Up:
            this->updatePosition(eventCode);
            break;
        case sf::Keyboard::Down:
            this->updatePosition(eventCode);
            break;
        case sf::Keyboard::Numpad1:
            this->_displayRessourceType = zappyGUI::Zappy2D::FOOD;
            break;
        case sf::Keyboard::Numpad2:
            this->_displayRessourceType = zappyGUI::Zappy2D::LINEMATE;
            break;
        case sf::Keyboard::Numpad3:
            this->_displayRessourceType = zappyGUI::Zappy2D::DERAUMERE;
            break;
        case sf::Keyboard::Numpad4:
            this->_displayRessourceType = zappyGUI::Zappy2D::SIBUR;
            break;
        case sf::Keyboard::Numpad5:
            this->_displayRessourceType = zappyGUI::Zappy2D::MENDIANE;
            break;
        case sf::Keyboard::Numpad6:
            this->_displayRessourceType = zappyGUI::Zappy2D::PHIRAS;
            break;
        case sf::Keyboard::Numpad7:
            this->_displayRessourceType = zappyGUI::Zappy2D::THYSTAME;
            break;
        case sf::Keyboard::Num1:
            this->_displayRessourceType = zappyGUI::Zappy2D::FOOD;
            break;
        case sf::Keyboard::Num2:
            this->_displayRessourceType = zappyGUI::Zappy2D::LINEMATE;
            break;
        case sf::Keyboard::Num3:
            this->_displayRessourceType = zappyGUI::Zappy2D::DERAUMERE;
            break;
        case sf::Keyboard::Num4:
            this->_displayRessourceType = zappyGUI::Zappy2D::SIBUR;
            break;
        case sf::Keyboard::Num5:
            this->_displayRessourceType = zappyGUI::Zappy2D::MENDIANE;
            break;
        case sf::Keyboard::Num6:
            this->_displayRessourceType = zappyGUI::Zappy2D::PHIRAS;
            break;
        case sf::Keyboard::Num7:
            this->_displayRessourceType = zappyGUI::Zappy2D::THYSTAME;
            break;
        default:
            break;
        
    }
    // this->tileSelection(game);
}

void zappyGUI::Zappy2D::tileSelection(Game &game)
{

}

zappyGUI::Zappy2D::AssetPool::AssetPool():
    _tileTexture(),
    _playerTexture(),
    _linemateTexture(),
    _deraumereTexture(),
    _siburTexture(),
    _mendianeTexture(),
    _phirasTexture(),
    _thystameTexture()
{
    this->_tileTexture.loadFromFile((ASSETS_FOLDER + std::string("tile1.png")));
    this->_playerTexture.loadFromFile((ASSETS_FOLDER + std::string("player1.png")));
    this->_linemateTexture.loadFromFile((ASSETS_FOLDER + std::string("ore1.png")));
    this->_deraumereTexture.loadFromFile((ASSETS_FOLDER + std::string("ore2.png")));
    this->_siburTexture.loadFromFile((ASSETS_FOLDER + std::string("ore3.png")));
    this->_mendianeTexture.loadFromFile((ASSETS_FOLDER + std::string("ore4.png")));
    this->_phirasTexture.loadFromFile((ASSETS_FOLDER + std::string("ore5.png")));
    this->_thystameTexture.loadFromFile((ASSETS_FOLDER + std::string("ore6.png")));
    this->_foodTexture.loadFromFile((ASSETS_FOLDER + std::string("food.png")));
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}
