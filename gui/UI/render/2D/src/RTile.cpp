/*
** EPITECH PROJECT, 2024
** zap
** File description:
** RTile.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::RTile::RTile(int x, int y, std::weak_ptr<zappyGUI::Zappy2D> ui):
    _back(),
    _ressource(),
    _ressourceAmount(),
    _ui(ui)
{
    if (auto ui =this->_ui.lock()) {

    float winX = x * (zappyGUI::BASE_TILE_SIZE * ui->getZoomCoeff()) + ui->getMapOffset().first;
    float winY = y * (zappyGUI::BASE_TILE_SIZE * ui->getZoomCoeff()) + ui->getMapOffset().second;

    this->_ressourceAmount.setFont(ui->_assets._font);
    this->_ressourceAmount.setScale(1.0, 1.0);
    this->_ressourceAmount.setColor(sf::Color::White);
    this->_back.setTexture(ui->getAssets()._tileTexture);
    this->_back.setScale(sf::Vector2f(1.0, 1.0));
    this->_back.setPosition(sf::Vector2f(winX, winY));
    }
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window) const
{
    window->getRenderWindow().draw(this->_back);
    window->getRenderWindow().draw(this->_ressource);
    window->getRenderWindow().draw(this->_ressourceAmount);
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    if (auto ui =this->_ui.lock()) {
        float x = tile.getPos().first * (zappyGUI::BASE_TILE_SIZE * ui->getZoomCoeff()) + ui->getMapOffset().first;
        float y = tile.getPos().second * (zappyGUI::BASE_TILE_SIZE * ui->getZoomCoeff()) + ui->getMapOffset().second;

        if (tile.getPlayers().size() >= 1) {
            this->updatePlayers(tile);
        } else {
            this->_back.setColor(sf::Color::White);
            this->_back.setTexture(ui->getAssets()._tileTexture);
        }
        if (tile.getRessourcesConst().size() >= 1)
            this->handleRessouces(tile);
        this->_back.setScale(sf::Vector2f(ui->getZoomCoeff(), ui->getZoomCoeff()));
        this->_back.setPosition(x, y);
    }
}

void zappyGUI::Zappy2D::RTile::updatePlayers(const zappyGUI::Tile &tile)
{
    for (const std::shared_ptr<zappyGUI::Player> &player : tile.getPlayers()) {
        if (player->isAlive()) {
            this->updatePlayer(tile, player);
            return;
        }
    }
    this->_back.setColor(sf::Color::White);
    if (auto ui =this->_ui.lock())
        this->_back.setTexture(ui->getAssets()._tileTexture);
}

void zappyGUI::Zappy2D::RTile::updatePlayer(const zappyGUI::Tile &tile, const  std::shared_ptr<zappyGUI::Player> &player)
{
    std::string team = tile.getPlayers().front()->getName();
    sf::Color color;

    if (team.size() >= 2)
        color = sf::Color(team[0] * 255 / 26, team[2] * 255 / 26, team[team.size() - 1] * 255 / 26);
    else if (team.size() == 1)
        color = sf::Color(team[0] * 255 / 26, team[0] * 255 / 26, team[0] * 255 / 26);
    if (auto ui =this->_ui.lock())
        this->_back.setTexture(ui->getAssets()._playerTexture);
    this->_back.setColor(color);
}

void zappyGUI::Zappy2D::RTile::handleRessouces(const zappyGUI::Tile &tile)
{
    const std::vector<std::pair<std::shared_ptr<zappyGUI::IRessource>, int>> &ressources = tile.getRessourcesConst();

    if (auto ui =this->_ui.lock()) {
        if (ui->getDisplayRessourceType() == zappyGUI::Zappy2D::ressourceType::ALL) {
            for (int type = 0; type < 7; type ++) {
                if (ressources[type].second > 0) {
                    this->setRessource(static_cast<zappyGUI::Zappy2D::ressourceType>(type), ressources[type].second);
                    return;
                }
            }
        } else if (ressources[ui->getDisplayRessourceType()].second <= 0) {
            this->_ressource.setColor(sf::Color::Transparent);
            this->_ressourceAmount.setColor(sf::Color::Transparent);
        } else
            this->setRessource(ui->getDisplayRessourceType(), ressources[ui->getDisplayRessourceType()].second);
    }
}

void zappyGUI::Zappy2D::RTile::setRessource(zappyGUI::Zappy2D::ressourceType ressourceType, int amount)
{
    if (auto ui =this->_ui.lock()) {
        float tileSize = zappyGUI::BASE_TILE_SIZE * ui->getZoomCoeff();
        float ressourceSize = zappyGUI::BASE_RESSOURCE_SIZE * ui->getZoomCoeff();
        float x = this->_back.getPosition().x + (tileSize / 2 - ressourceSize / 2);
        float y = this->_back.getPosition().y + (tileSize / 2 - ressourceSize / 2);

        this->_ressource.setScale(sf::Vector2f(ui->getZoomCoeff(), ui->getZoomCoeff()));
        this->_ressource.setPosition(x, y);
        this->_ressourceAmount.setColor(sf::Color::White);
        this->_ressourceAmount.setPosition(x, y);
        this->_ressourceAmount.setCharacterSize(RESSOURCE_FONT_SIZE);
        this->_ressourceAmount.setString(std::to_string(5));
        this->setRessourceTexture(ressourceType);
        this->_ressource.setColor(sf::Color::White);
    }
}

void zappyGUI::Zappy2D::RTile::setRessourceTexture(zappyGUI::Zappy2D::ressourceType ressourceType)
{
    if (auto ui =this->_ui.lock()) {
        switch(ressourceType) {
            case zappyGUI::Zappy2D::FOOD:
                this->_ressource.setTexture(ui->getAssets()._foodTexture);
                break;
            case zappyGUI::Zappy2D::LINEMATE:
                this->_ressource.setTexture(ui->getAssets()._linemateTexture);
                break;
            case zappyGUI::Zappy2D::DERAUMERE:
                this->_ressource.setTexture(ui->getAssets()._deraumereTexture);
                break;
            case zappyGUI::Zappy2D::SIBUR:
                this->_ressource.setTexture(ui->getAssets()._siburTexture);
                break;
            case zappyGUI::Zappy2D::MENDIANE:
                this->_ressource.setTexture(ui->getAssets()._mendianeTexture);
                break;
            case zappyGUI::Zappy2D::PHIRAS:
                this->_ressource.setTexture(ui->getAssets()._phirasTexture);
                break;
            case zappyGUI::Zappy2D::THYSTAME:
                this->_ressource.setTexture(ui->getAssets()._thystameTexture);
                break;
        }
    }
}
