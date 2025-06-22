/*
** EPITECH PROJECT, 2024
** zap
** File description:
** RTile.cpp
*/

#include "Zappy2D.hpp"

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
        this->updatePlayers(tile);
    } else {
        this->_back.setTexture(this->_assets->_tileTexture);
        if (tile.getRessourcesConst().size() >= 1) {
            this->handleRessouces(tile);
        }
    }
    this->_back.setScale(sf::Vector2f(*this->_zoomCoeff.get(), *this->_zoomCoeff.get()));
    this->_back.setPosition(x, y);
}
// letter * 255 / 26

void zappyGUI::Zappy2D::RTile::updatePlayers(const zappyGUI::Tile &tile)
{
    // sf::Color color();
    this->_back.setTexture(this->_assets->_playerTexture);
    this->_back.setColor(sf::Color::Red);
}
