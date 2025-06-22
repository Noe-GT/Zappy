/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "Player.hpp"
#include <iostream>
zappyGUI::Game::Game() : _frequence(0), _teamNbr(0), _gameInProgess(false), _mapSize(30, 30), _selectedPlayer(nullptr)
{
    for (size_t y = 0; y < this->_mapSize.second; y++) {
        this->_map.emplace_back();
        for (size_t x = 0; x < this->_mapSize.first; x++)
            this->_map.back().emplace_back(std::pair<size_t, size_t>(x, y));
    }
    
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> emptyList;
    this->_playersListUI = std::make_shared<UIBlocks::List>(emptyList, std::pair<float, float>(50, 300), std::pair<float, float>(200, 400));
    this->_selectedPlayerLevelText = std::make_shared<UIBlocks::Text>("Level: 0", std::pair<float, float>(960, 50), 24);
    this->_inventoryBarUI = std::make_shared<UIBlocks::List>(emptyList, std::pair<float, float>(760, 900), std::pair<float, float>(400, 100));
    this->_spellsListUI = std::make_shared<UIBlocks::List>(emptyList, std::pair<float, float>(1670, 300), std::pair<float, float>(200, 400));
}

zappyGUI::Game::~Game()
{
}

int zappyGUI::Game::getFrequence()
{
    return this->_frequence;
}

int zappyGUI::Game::getTeamNbr()
{
    return this->_teamNbr;
}

bool zappyGUI::Game::isGameInProgess()
{
    return this->_gameInProgess;
}

std::vector <std::string> &zappyGUI::Game::getLogs()
{
    return this->_logs;
}

std::vector <std::vector <zappyGUI::Tile>> &zappyGUI::Game::getMap()
{
    return this->_map;
}

std::pair<size_t, size_t> zappyGUI::Game::getMapSize()
{
    return this->_mapSize;
}

std::vector <zappyGUI::Player> &zappyGUI::Game::getPlayers()
{
    return this->_players;
}

std::vector <std::pair<std::shared_ptr <zappyGUI::Player>, int>> &zappyGUI::Game::getEggs()
{
    return this->_eggs;
}

std::vector <std::string> &zappyGUI::Game::getTeams()
{
    return this->_teams;
}

void zappyGUI::Game::setFrequence(int newVal)
{
    this->_frequence = newVal;
}

void zappyGUI::Game::setTeamNbr(int newVal)
{
    this->_teamNbr = newVal;
}

void zappyGUI::Game::setIsGameInProgess(bool newVal)
{
    this->_gameInProgess = newVal;
}

void zappyGUI::Game::setLogs(std::vector <std::string> newVal)
{
    this->_logs = newVal;
}

void zappyGUI::Game::addLogs(std::string newVal)
{
    this->_logs.push_back(newVal);
}

void zappyGUI::Game::setMap(std::vector <std::vector <zappyGUI::Tile>> newVal)
{
    this->_map = newVal;
}

void zappyGUI::Game::setMapSize(int newX, int newY)
{
    this->_mapSize = {newX, newY};
    this->_map.clear();
    this->_map.resize(newY);
    for (int y = 0; y < newY; y++) {
        this->_map[y].reserve(newX);
        for (int x = 0; x < newX; x++)
            this->_map[y].emplace_back(std::make_pair(x, y));
    }
    std::clog << "map have now a size of " << this->_map.size() << "x" << (this->_map.empty() ? 0 : this->_map[0].size()) << std::endl;
}

void zappyGUI::Game::setPlayers(std::vector <zappyGUI::Player> newVal)
{
    this->_players = newVal;
}

void zappyGUI::Game::addPlayer(zappyGUI::Player newVal)
{
    this->_players.push_back(newVal);
}

void zappyGUI::Game::setEggs(std::vector <std::pair <std::shared_ptr <zappyGUI::Player>, int>> newVal)
{
    this->_eggs = newVal;
}

void zappyGUI::Game::addEgg(std::shared_ptr <zappyGUI::Player> newVal, int ID)
{
    this->_eggs.push_back({newVal, ID});
}

void zappyGUI::Game::setTeams(std::vector <std::string> newVal)
{
    this->_teams = newVal;
}

void zappyGUI::Game::addTeam(std::string newVal)
{
    this->_teams.push_back(newVal);
}

void zappyGUI::Game::display(std::shared_ptr<zappyGUI::IGraphical> renderer)
{
    for (const std::vector<zappyGUI::Tile> &tileRow : this->_map) {
        for (const zappyGUI::Tile &tile : tileRow) {
            renderer->updateTile(tile);
            renderer->displayTile(tile);
        }
    }
    this->displayUI(renderer->getWindow());
}

void zappyGUI::Game::displayUI(std::shared_ptr<zappyGUI::Window> window)
{
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> playerTexts;
    for (size_t i = 0; i < this->_players.size(); ++i) {
        std::string playerInfo = "Player " + std::to_string(this->_players[i].getId()) + " - " + this->_players[i].getName();
        std::shared_ptr<UIBlocks::Text> playerText = std::make_shared<UIBlocks::Text>(playerInfo, std::pair<float, float>(0, 0), 16);
        playerTexts.push_back(playerText);
    }
    this->_playersListUI = std::make_shared<UIBlocks::List>(playerTexts, std::pair<float, float>(50, 300), std::pair<float, float>(200, 400));
    if (this->_selectedPlayer) {
        std::string levelText = "Level: " + std::to_string(this->_selectedPlayer->getLvl());
        this->_selectedPlayerLevelText->setText(levelText);
        std::vector<std::shared_ptr<UIBlocks::IUIBlock>> inventoryTexts;
        std::__1::vector<std::__1::pair<std::__1::shared_ptr<zappyGUI::IRessource>, int>> &inventory = this->_selectedPlayer->getInventory();
        std::vector<std::string> resourceNames = {"Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"};
        for (size_t i = 0; i < inventory.size() && i < resourceNames.size(); ++i) {
            std::string itemText = resourceNames[i] + ": " + std::to_string(inventory[i].second);
            std::shared_ptr<UIBlocks::Text> itemDisplay = std::make_shared<UIBlocks::Text>(itemText, std::pair<float, float>(0, 0), 14);
            inventoryTexts.push_back(itemDisplay);
        }
        this->_inventoryBarUI = std::make_shared<UIBlocks::List>(inventoryTexts, std::pair<float, float>(760, 900), std::pair<float, float>(400, 100));
    }
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> spellTexts;
    for (auto& player : this->_players) {
        if (player.getSpellInProgress() != nullptr) {
            std::string spellText = "Player " + std::to_string(player.getId()) + " - Casting Spell";
            std::shared_ptr<UIBlocks::Text> spellDisplay = std::make_shared<UIBlocks::Text>(spellText, std::pair<float, float>(0, 0), 16);
            spellTexts.push_back(spellDisplay);
        }
    }
    this->_spellsListUI = std::make_shared<UIBlocks::List>(spellTexts, std::pair<float, float>(1670, 300), std::pair<float, float>(200, 400));
    this->_playersListUI->draw(window);
    this->_selectedPlayerLevelText->draw(window);
    this->_inventoryBarUI->draw(window);
    this->_spellsListUI->draw(window);
}

void zappyGUI::Game::handleUIEvents(const sf::Event& event, std::shared_ptr<zappyGUI::Window> window)
{
    // Handle player selection from the players list
    // if (event.type == sf::Event::MouseButtonPressed) {
    //     if (event.mouseButton.button == sf::Mouse::Left) {
    //         // Check if click is within players list bounds
    //         sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            
    //         // Simple click detection for player list (middle left area)
    //         if (mousePos.x >= 50 && mousePos.x <= 250 && mousePos.y >= 300 && mousePos.y <= 700) {
    //             // Calculate which player was clicked based on position
    //             int playerIndex = (mousePos.y - 300) / 25; // Assuming 25 pixel height per player entry
    //             if (playerIndex >= 0 && playerIndex < static_cast<int>(_players.size())) {
    //                 _selectedPlayer = _players[playerIndex];
    //             }
    //         }
    //     }
    // }
    
    // // Let UI blocks handle their own events
    if (this->_playersListUI)
        this->_playersListUI->handleEvent(event, window);
    if (this->_selectedPlayerLevelText)
        this->_selectedPlayerLevelText->handleEvent(event, window);
    if (this->_inventoryBarUI)
        this->_inventoryBarUI->handleEvent(event, window);
    if (this->_spellsListUI)
        this->_spellsListUI->handleEvent(event, window);
}

std::shared_ptr<zappyGUI::Player> zappyGUI::Game::getSelectedPlayer()
{
    return _selectedPlayer;
}
