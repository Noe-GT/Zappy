/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy2D.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D():
    _tiles(),
    _zoomCoeff(std::make_shared<double>(1.0))
{
}

void zappyGUI::Zappy2D::initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize)
{
    zappyGUI::AGraphical::initialize(window, mapSize);
    // if (mapSize.first * BASE_TILE_SIZE > window->getSize().first ||
    //     mapSize.second * BASE_TILE_SIZE > window->getSize().second) {
    //     *this->_zoomCoeff.get() = std::min(
    //         static_cast<double>(window->getSize().first) / (mapSize.first * BASE_TILE_SIZE),
    //         static_cast<double>(window->getSize().second) / (mapSize.second * BASE_TILE_SIZE));
    // } else {
    //     *this->_zoomCoeff.get() = 1.0;
    // }
    for (size_t y = 0; y < mapSize.second; y++) {
        this->_tiles.emplace_back();
        for (size_t x = 0; x < mapSize.first; x++)
            this->_tiles.back().emplace_back(x, y, this->_zoomCoeff);
    }
}

void zappyGUI::Zappy2D::handleEvents()
{
    if (this->_window->getEvent().key.code == sf::Keyboard::Add)
        this->updateZoom(false);
    else if (this->_window->getEvent().key.code == sf::Keyboard::Subtract)
        this->updateZoom(true);
}

void zappyGUI::Zappy2D::updateZoom(bool zoomOut)
{
    if (zoomOut && *this->_zoomCoeff.get() > ZOOM_COEFF_MIN) {
        *this->_zoomCoeff.get() -= ZOOM_COEFF_SENSITIVITY;
    } else if (!zoomOut && *this->_zoomCoeff.get() < ZOOM_COEFF_MAX) {
        *this->_zoomCoeff.get() += ZOOM_COEFF_SENSITIVITY;
    }
    // printf("Zooming %s : %lf\n", zoomOut ? "out" : "in", *this->_zoomCoeff.get());
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

zappyGUI::Zappy2D::RTile::RTile(int x, int y, std::shared_ptr<double> zoomCoeff):
    _zoomCoeff(zoomCoeff),
    _back(),
    _players()
{
    this->_back.setSize(sf::Vector2f(BASE_TILE_SIZE * (*zoomCoeff.get()), BASE_TILE_SIZE * (*zoomCoeff.get())));
    this->_back.setFillColor(sf::Color::White);
    this->_back.setOutlineThickness(2);
    this->_back.setOutlineColor(sf::Color::Red);
    this->_back.setPosition(sf::Vector2f(x * (BASE_TILE_SIZE * (*zoomCoeff.get())), y * (BASE_TILE_SIZE * (*zoomCoeff.get()))));
}

void zappyGUI::Zappy2D::RTile::display(std::shared_ptr<zappyGUI::Window> window) const
{
    window->getRenderWindow().draw(this->_back);
    for (const sf::CircleShape &player : this->_players)
        window->getRenderWindow().draw(player);
}

void zappyGUI::Zappy2D::RTile::update(const zappyGUI::Tile &tile)
{
    this->_players.clear();
    for (const std::shared_ptr<zappyGUI::Player> &player : tile.getPlayers()) {
        sf::CircleShape playerShape(BASE_PLAYER_SIZE * *this->_zoomCoeff.get());
        playerShape.setFillColor(sf::Color::Green);
        playerShape.setPosition(this->_back.getPosition().x + BASE_TILE_SIZE,
                                this->_back.getPosition().y + BASE_TILE_SIZE);
        this->_players.push_back(playerShape);
        (void)player;
    }
    // printf("Updating tile at (%zu, %zu) with %d coeff\n", tile.getPos().first, tile.getPos().second, *this->_zoomCoeff.get());
    this->_back.setSize(sf::Vector2f(BASE_TILE_SIZE * *this->_zoomCoeff.get(), BASE_TILE_SIZE * *this->_zoomCoeff.get()));
    this->_back.setPosition(sf::Vector2f(tile.getPos().first * (BASE_TILE_SIZE * *this->_zoomCoeff.get()),
                                tile.getPos().second * (BASE_TILE_SIZE * *this->_zoomCoeff.get())));
    this->_back.setOutlineThickness(2 * *this->_zoomCoeff.get());
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}
