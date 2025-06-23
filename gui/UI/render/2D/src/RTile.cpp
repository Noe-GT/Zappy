/*
** EPITECH PROJECT, 2024
** zap
** File description:
** RTile.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::RTile::RTile(int x, int y, std::shared_ptr<zappyGUI::Zappy2D> ui):
    _back(),
    _ressource(),
    _ui(ui)
{
    float winX = x * (zappyGUI::BASE_TILE_SIZE * ui->getZoomCoeff() + ui->getMapOffset().first);
    float winY = y * (zappyGUI::BASE_TILE_SIZE * ui->getZoomCoeff() + ui->getMapOffset().second);

    this->_back.setTexture(ui->getAssets()._tileTexture);
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

    if (ressources[this->_ui->getDisplayRessourceType()].second <= 0)
        this->_ressource.setColor(sf::Color::Transparent);
    else
        this->setRessource();
}

void zappyGUI::Zappy2D::RTile::setRessource()
{
    float tileSize = zappyGUI::BASE_TILE_SIZE * this->_ui->getZoomCoeff();
    float ressourceSize = zappyGUI::BASE_RESSOURCE_SIZE * this->_ui->getZoomCoeff();
    float x = this->_back.getPosition().x + (tileSize / 2 - ressourceSize / 2);
    float y = this->_back.getPosition().y + (tileSize / 2 - ressourceSize / 2);

    this->_ressource.setScale(sf::Vector2f(this->_ui->getZoomCoeff(), this->_ui->getZoomCoeff()));
    this->_ressource.setPosition(x, y);
    this->setRessourceTexture();
    this->_ressource.setColor(sf::Color::White);
}

void zappyGUI::Zappy2D::RTile::setRessourceTexture()
{
    switch(this->_ui->getDisplayRessourceType()) {
        case zappyGUI::Zappy2D::FOOD:
            this->_ressource.setTexture(this->_ui->getAssets()._foodTexture);
            break;
        case zappyGUI::Zappy2D::LINEMATE:
            this->_ressource.setTexture(this->_ui->getAssets()._linemateTexture);
            break;
        case zappyGUI::Zappy2D::DERAUMERE:
            this->_ressource.setTexture(this->_ui->getAssets()._deraumereTexture);
            break;
        case zappyGUI::Zappy2D::SIBUR:
            this->_ressource.setTexture(this->_ui->getAssets()._siburTexture);
            break;
        case zappyGUI::Zappy2D::MENDIANE:
            this->_ressource.setTexture(this->_ui->getAssets()._mendianeTexture);
            break;
        case zappyGUI::Zappy2D::PHIRAS:
            this->_ressource.setTexture(this->_ui->getAssets()._phirasTexture);
            break;
        case zappyGUI::Zappy2D::THYSTAME:
            this->_ressource.setTexture(this->_ui->getAssets()._thystameTexture);
            break;
    }
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    float x = tile.getPos().first * (zappyGUI::BASE_TILE_SIZE * this->_ui->getZoomCoeff()) + this->_ui->getMapOffset().first;
    float y = tile.getPos().second * (zappyGUI::BASE_TILE_SIZE * this->_ui->getZoomCoeff()) + this->_ui->getMapOffset().second;

    if (tile.getPlayers().size() >= 1)
        this->updatePlayers(tile);
    else
        this->_back.setTexture(this->_ui->getAssets()._tileTexture);
    if (tile.getRessourcesConst().size() >= 1)
        this->handleRessouces(tile);
    this->_back.setScale(sf::Vector2f(this->_ui->getZoomCoeff(), this->_ui->getZoomCoeff()));
    this->_back.setPosition(x, y);
}

void zappyGUI::Zappy2D::RTile::updatePlayers(const zappyGUI::Tile &tile)
{
    std::string team = tile.getPlayers().front()->getName();
    sf::Color color;

    if (team.size() >= 2)
        color = sf::Color(team[0] * 255 / 26, team[2] * 255 / 26, team[team.size() - 1] * 255 / 26);
    else if (team.size() == 1)
        color = sf::Color(team[0] * 255 / 26, team[0] * 255 / 26, team[0] * 255 / 26);
    else
        color = sf::Color(sf::Color::White);
    this->_back.setTexture(this->_ui->getAssets()._playerTexture);
    this->_back.setColor(color);
}
