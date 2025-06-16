/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy2D.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D():
    _assets(std::make_shared<zappyGUI::Zappy2D::AssetPool>()),
    _tiles(),
    _zoomCoeff(std::make_shared<double>(1.0)),
    _mapOffset(std::make_shared<std::pair<double, double>>(std::pair<double, double>(200.00, 20.0)))
{
}

void zappyGUI::Zappy2D::initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize)
{
    zappyGUI::AGraphical::initialize(window, mapSize);
    for (size_t y = 0; y < mapSize.second; y++) {
        this->_tiles.emplace_back();
        for (size_t x = 0; x < mapSize.first; x++)
            this->_tiles.back().emplace_back(x, y, this->_zoomCoeff, this->_mapOffset, this->_assets);
    }
    this->_mapOffset->first = (window->getSize().first - (mapSize.first * BASE_TILE_SIZE)) / 2.0;
    this->_mapOffset->second = (window->getSize().second - (mapSize.second * BASE_TILE_SIZE)) / 2.0;
}

void zappyGUI::Zappy2D::handleEvents()
{
    sf::Keyboard::Key eventCode = this->_window->getEvent().key.code;

    switch (eventCode) {
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
        default:
            break;
    }
}

void zappyGUI::Zappy2D::updateZoom(bool zoomOut)
{
    if (zoomOut && *this->_zoomCoeff.get() > ZOOM_COEFF_MIN) {
        *this->_zoomCoeff.get() -= ZOOM_COEFF_SENSITIVITY;
    } else if (!zoomOut && *this->_zoomCoeff.get() < ZOOM_COEFF_MAX) {
        *this->_zoomCoeff.get() += ZOOM_COEFF_SENSITIVITY;
    }
}

void zappyGUI::Zappy2D::updatePosition(sf::Keyboard::Key eventCode)
{
    if (eventCode == sf::Keyboard::Right) {
        (*this->_mapOffset.get()).first += MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
    } else if (eventCode == sf::Keyboard::Left) {
        (*this->_mapOffset.get()).first -= MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
    } else if (eventCode == sf::Keyboard::Up) {
        (*this->_mapOffset.get()).second -= MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
    } else if (eventCode == sf::Keyboard::Down) {
        (*this->_mapOffset.get()).second += MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
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

zappyGUI::Zappy2D::RTile::RTile(int x, int y, std::shared_ptr<double> zoomCoeff,
    std::shared_ptr<std::pair<double, double>> mapOffset, std::shared_ptr<zappyGUI::Zappy2D::AssetPool> assets):
    _zoomCoeff(zoomCoeff),
    _mapOffset(mapOffset),
    _assets(assets),
    _back(),
    _ressource()
{
    double winX;
    double winY;

    this->_back.setTexture(assets->_tileTexture);
    this->_back.setScale(sf::Vector2f(1.0, 1.0));
    winX = x * (BASE_TILE_SIZE * (*zoomCoeff.get())) + (*mapOffset.get()).first;
    winY = y * (BASE_TILE_SIZE * (*zoomCoeff.get())) + (*mapOffset.get()).second;
    this->_back.setPosition(sf::Vector2f(winX, winY));
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window) const
{
    window->getRenderWindow().draw(this->_back);
    window->getRenderWindow().draw(this->_ressource);
}

void zappyGUI::Zappy2D::RTile::handleRessouces(const zappyGUI::Tile &tile)
{
    zappyGUI::IRessource *ressource = tile.getRessourcesConst()[0].first.get();
    float tileSize = BASE_TILE_SIZE * *this->_zoomCoeff.get();
    float ressourceSize = BASE_RESSOURCE_SIZE * *this->_zoomCoeff.get();
    float x = this->_back.getPosition().x + (tileSize / 2 - ressourceSize / 2);
    float y = this->_back.getPosition().y + (tileSize / 2 - ressourceSize / 2);

    this->_ressource.setScale(sf::Vector2f(*this->_zoomCoeff.get(), *this->_zoomCoeff.get()));
    this->_ressource.setPosition(x, y);
    this->_ressource.setTexture(this->_assets->_linemateTexture);
    if (dynamic_cast<zappyGUI::Food*>(ressource))
        this->_ressource.setTexture(this->_assets->_foodTexture);
    else if (dynamic_cast<zappyGUI::Linemate*>(ressource))
        this->_ressource.setTexture(this->_assets->_linemateTexture);
    else if (dynamic_cast<zappyGUI::Deraumere*>(ressource))
        this->_ressource.setTexture(this->_assets->_deraumereTexture);
    else if (dynamic_cast<zappyGUI::Sibur*>(ressource))
        this->_ressource.setTexture(this->_assets->_siburTexture);
    else if (dynamic_cast<zappyGUI::Mendiane*>(ressource))
        this->_ressource.setTexture(this->_assets->_mendianeTexture);
    else if (dynamic_cast<zappyGUI::Phiras*>(ressource))
        this->_ressource.setTexture(this->_assets->_phirasTexture);
    else if (dynamic_cast<zappyGUI::Thystame*>(ressource))
        this->_ressource.setTexture(this->_assets->_thystameTexture);
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    float x = tile.getPos().first * (BASE_TILE_SIZE * *this->_zoomCoeff.get()) + (*this->_mapOffset.get()).first;
    float y = tile.getPos().second * (BASE_TILE_SIZE * *this->_zoomCoeff.get()) + (*this->_mapOffset.get()).second;

    if (tile.getPlayers().size() >= 1) {
        this->_back.setTexture(this->_assets->_playerTexture);
        this->_back.setColor(sf::Color::Red);
    } else {
        this->_back.setTexture(this->_assets->_tileTexture);
        if (tile.getRessourcesConst().size() >= 1) {
            this->handleRessouces(tile);
        }
    }
    this->_back.setScale(sf::Vector2f(*this->_zoomCoeff.get(), *this->_zoomCoeff.get()));
    this->_back.setPosition(x, y);
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
    this->_deraumereTexture.loadFromFile((ASSETS_FOLDER + std::string("ore7.png")));
    this->_siburTexture.loadFromFile((ASSETS_FOLDER + std::string("ore3.png")));
    this->_mendianeTexture.loadFromFile((ASSETS_FOLDER + std::string("ore2.png")));
    this->_phirasTexture.loadFromFile((ASSETS_FOLDER + std::string("ore5.png")));
    this->_thystameTexture.loadFromFile((ASSETS_FOLDER + std::string("ore6.png")));
    this->_foodTexture.loadFromFile((ASSETS_FOLDER + std::string("food.png")));
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}
