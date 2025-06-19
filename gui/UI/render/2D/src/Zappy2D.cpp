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
    _zoomCoeff(std::make_shared<float>(1.0)),
    _mapOffset(std::make_shared<std::pair<float, float>>(std::pair<float, float>(200.00, 20.0))),
    _displayRessourceType(std::make_shared<zappyGUI::Zappy2D::ressourceType>(zappyGUI::Zappy2D::FOOD))
{
}

void zappyGUI::Zappy2D::initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize)
{
    zappyGUI::AGraphical::initialize(window, mapSize);
    for (size_t y = 0; y < mapSize.second; y++) {
        this->_tiles.emplace_back();
        for (size_t x = 0; x < mapSize.first; x++)
            this->_tiles.back().emplace_back(x, y, this->_zoomCoeff, this->_mapOffset, this->_assets, this->_displayRessourceType);
    }
    this->_mapOffset->first = (window->getSize().first - (mapSize.first * zappyGUI::BASE_TILE_SIZE)) / 2.0;
    this->_mapOffset->second = (window->getSize().second - (mapSize.second * zappyGUI::BASE_TILE_SIZE)) / 2.0;
}


void zappyGUI::Zappy2D::computeZoom(std::pair<size_t, size_t> mapSize)
{
    if (mapSize.first == 0 || mapSize.second == 0)
        return;
    float windowWidth = this->_window->getSize().first;
    float windowHeight = this->_window->getSize().second;
    // double availableWidth = windowWidth * (1.0 - 2 * MARGIN_HORIZONTAL);
    // double availableHeight = windowHeight - (2 * MARGIN_VERTICAL);
    if (windowHeight < 1.0)
        windowHeight = 1.0;
    float widthRatio = windowWidth / (mapSize.first * zappyGUI::BASE_TILE_SIZE);
    float heightRatio = windowHeight / (mapSize.second * zappyGUI::BASE_TILE_SIZE);
    *this->_zoomCoeff.get() = std::min(widthRatio, heightRatio);
    *this->_zoomCoeff.get() = std::max(std::min(*this->_zoomCoeff.get(), zappyGUI::ZOOM_COEFF_MAX), zappyGUI::ZOOM_COEFF_MIN);
    // std::cout << _zoomCoeff << std::endl;
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
        case sf::Keyboard::Numpad1:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::FOOD;
            break;
        case sf::Keyboard::Numpad2:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::LINEMATE;
            break;
        case sf::Keyboard::Numpad3:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::DERAUMERE;
            break;
        case sf::Keyboard::Numpad4:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::SIBUR;
            break;
        case sf::Keyboard::Numpad5:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::MENDIANE;
            break;
        case sf::Keyboard::Numpad6:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::PHIRAS;
            break;
        case sf::Keyboard::Numpad7:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::THYSTAME;
            break;
        case sf::Keyboard::Num1:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::FOOD;
            break;
        case sf::Keyboard::Num2:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::LINEMATE;
            break;
        case sf::Keyboard::Num3:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::DERAUMERE;
            break;
        case sf::Keyboard::Num4:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::SIBUR;
            break;
        case sf::Keyboard::Num5:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::MENDIANE;
            break;
        case sf::Keyboard::Num6:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::PHIRAS;
            break;
        case sf::Keyboard::Num7:
            *this->_displayRessourceType.get() = zappyGUI::Zappy2D::THYSTAME;
            break;
        default:
            break;
    }
}

void zappyGUI::Zappy2D::updateZoom(bool zoomOut)
{
    if (zoomOut && *this->_zoomCoeff.get() > zappyGUI::ZOOM_COEFF_MIN) {
        *this->_zoomCoeff.get() -= zappyGUI::ZOOM_COEFF_SENSITIVITY;
    } else if (!zoomOut && *this->_zoomCoeff.get() < zappyGUI::ZOOM_COEFF_MAX) {
        *this->_zoomCoeff.get() += zappyGUI::ZOOM_COEFF_SENSITIVITY;
    }
}

void zappyGUI::Zappy2D::updatePosition(sf::Keyboard::Key eventCode)
{
    if (eventCode == sf::Keyboard::Right) {
        (*this->_mapOffset.get()).first += zappyGUI::MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
    } else if (eventCode == sf::Keyboard::Left) {
        (*this->_mapOffset.get()).first -= zappyGUI::MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
    } else if (eventCode == sf::Keyboard::Up) {
        (*this->_mapOffset.get()).second -= zappyGUI::MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
    } else if (eventCode == sf::Keyboard::Down) {
        (*this->_mapOffset.get()).second += zappyGUI::MAP_OFFSET_SENSITIVITY * (*this->_zoomCoeff.get());
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

zappyGUI::Zappy2D::RTile::RTile(int x, int y, std::shared_ptr<float> zoomCoeff,
    std::shared_ptr<std::pair<float, float>> mapOffset, std::shared_ptr<zappyGUI::Zappy2D::AssetPool> assets,
    std::shared_ptr<zappyGUI::Zappy2D::ressourceType> displayRessourceType
):
    _zoomCoeff(zoomCoeff),
    _mapOffset(mapOffset),
    _displayRessourceType(displayRessourceType),
    _assets(assets),
    _back(),
    _ressource()
{
    float winX = x * (zappyGUI::BASE_TILE_SIZE * (*zoomCoeff.get())) + (*mapOffset.get()).first;
    float winY = y * (zappyGUI::BASE_TILE_SIZE * (*zoomCoeff.get())) + (*mapOffset.get()).second;

    this->_back.setTexture(assets->_tileTexture);
    this->_back.setScale(sf::Vector2f(1.0, 1.0));
    this->_back.setPosition(sf::Vector2f(winX, winY));
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window) const
{
    window->getRenderWindow().draw(this->_back);
    window->getRenderWindow().draw(this->_ressource);
}

void zappyGUI::Zappy2D::RTile::handleRessouces(const zappyGUI::Tile &tile)
{
    const std::vector<std::pair<std::shared_ptr<zappyGUI::IRessource>, int>> &ressources = tile.getRessourcesConst();

    if (tile.getPos().first == 0 && tile.getPos().second == 0) {
        std::cout << "ressource:" << ressources[*this->_displayRessourceType.get()].second << std::endl;
    }
    if (ressources[*this->_displayRessourceType.get()].second <= 0)
        this->_ressource.setColor(sf::Color::Transparent);
    else
        this->setRessource();
}

void zappyGUI::Zappy2D::RTile::setRessource()
{
    float tileSize = zappyGUI::BASE_TILE_SIZE * *this->_zoomCoeff.get();
    float ressourceSize = zappyGUI::BASE_RESSOURCE_SIZE * *this->_zoomCoeff.get();
    float x = this->_back.getPosition().x + (tileSize / 2 - ressourceSize / 2);
    float y = this->_back.getPosition().y + (tileSize / 2 - ressourceSize / 2);

    this->_ressource.setScale(sf::Vector2f(*this->_zoomCoeff.get(), *this->_zoomCoeff.get()));
    this->_ressource.setPosition(x, y);
    this->setRessourceTexture();
    this->_ressource.setColor(sf::Color::White);
}

void zappyGUI::Zappy2D::RTile::setRessourceTexture()
{
    switch(*this->_displayRessourceType.get()) {
        case zappyGUI::Zappy2D::FOOD:
            this->_ressource.setTexture(this->_assets->_foodTexture);
            break;
        case zappyGUI::Zappy2D::LINEMATE:
            this->_ressource.setTexture(this->_assets->_linemateTexture);
            break;
        case zappyGUI::Zappy2D::DERAUMERE:
            this->_ressource.setTexture(this->_assets->_deraumereTexture);
            break;
        case zappyGUI::Zappy2D::SIBUR:
            this->_ressource.setTexture(this->_assets->_siburTexture);
            break;
        case zappyGUI::Zappy2D::MENDIANE:
            this->_ressource.setTexture(this->_assets->_mendianeTexture);
            break;
        case zappyGUI::Zappy2D::PHIRAS:
            this->_ressource.setTexture(this->_assets->_phirasTexture);
            break;
        case zappyGUI::Zappy2D::THYSTAME:
            this->_ressource.setTexture(this->_assets->_thystameTexture);
            break;
    }
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    float x = tile.getPos().first * (zappyGUI::BASE_TILE_SIZE * *this->_zoomCoeff.get()) + (*this->_mapOffset.get()).first;
    float y = tile.getPos().second * (zappyGUI::BASE_TILE_SIZE * *this->_zoomCoeff.get()) + (*this->_mapOffset.get()).second;

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
