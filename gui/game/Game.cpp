/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "Player.hpp"
#include "../UI/shared/IGraphical.hpp"

zappyGUI::Game::Game() : _frequence(0), _teamNbr(0), _gameInProgess(false), _mapSize(30, 30), _selectedPlayer(nullptr)
{
    for (size_t y = 0; y < this->_mapSize.second; y++) {
        this->_map.emplace_back();
        for (size_t x = 0; x < this->_mapSize.first; x++)
            this->_map.back().emplace_back(std::pair<size_t, size_t>(x, y));
    }
    
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> emptyList;
    this->_playersListUI = std::make_shared<UIBlocks::PopupSelector>(emptyList, std::pair<float, float>(50, 300), std::pair<float, float>(200, 400));
    this->_playersListUI->open();
    this->_selectedPlayerLevelText = std::make_shared<UIBlocks::Text>("Level -1", std::pair<float, float>(760, 50), 24);
    this->_spellsListUI = std::make_shared<UIBlocks::List>(emptyList, std::pair<float, float>(1670, 300), std::pair<float, float>(200, 400));
    zappyGUI::Player player;
    player.setId(0);
    player.setName("Default Player");
    player.setLvl(1);
    player.setPos(std::make_pair(30, 30));
    player.setOrientation(zappyGUI::orientation::NORTH);
    player.setInventory({
        {std::make_shared<zappyGUI::Food>(), 0},
        {std::make_shared<zappyGUI::Linemate>(), 25},
        {std::make_shared<zappyGUI::Deraumere>(), 0},
        {std::make_shared<zappyGUI::Sibur>(), 10},
        {std::make_shared<zappyGUI::Mendiane>(), 0},
        {std::make_shared<zappyGUI::Phiras>(), 0},
        {std::make_shared<zappyGUI::Thystame>(), 30}
    });
    this->_players.push_back(player);
    this->_selectedPlayer = std::make_shared<zappyGUI::Player>(player);
    this->_map.at(0).at(0).addPlayer(this->_selectedPlayer);
    this->_inventoryUI = {
        {"Food", {UIBlocks::Text("Food: ", std::pair<float, float>(50, 50), 16), UIBlocks::Text("0", std::pair<float, float>(150, 50), 16)}},
        {"Linemate", {UIBlocks::Text("Linemate: ", std::pair<float, float>(50, 70), 16), UIBlocks::Text("0", std::pair<float, float>(150, 70), 16)}},
        {"Deraumere", {UIBlocks::Text("Deraumere: ", std::pair<float, float>(50, 90), 16), UIBlocks::Text("0", std::pair<float, float>(150, 90), 16)}},
        {"Sibur", {UIBlocks::Text("Sibur: ", std::pair<float, float>(50, 110), 16), UIBlocks::Text("0", std::pair<float, float>(150, 110), 16)}},
        {"Mendiane", {UIBlocks::Text("Mendiane: ", std::pair<float, float>(50, 130), 16), UIBlocks::Text("0", std::pair<float, float>(150, 130), 16)}},
        {"Phiras", {UIBlocks::Text("Phiras: ", std::pair<float, float>(50, 150), 16), UIBlocks::Text("0", std::pair<float, float>(150, 150), 16)}},
        {"Thystame", {UIBlocks::Text("Thystame: ", std::pair<float, float>(50, 170), 16), UIBlocks::Text("0", std::pair<float, float>(150, 170), 16)}}
    };
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

const std::pair<size_t, size_t> &zappyGUI::Game::getMapSize() const
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
    this->_playersListUI = std::make_shared<UIBlocks::PopupSelector>(playerTexts, std::pair<float, float>(50, 300), std::pair<float, float>(200, 400));
    if (this->_selectedPlayer) {
        std::string levelText = "Level " + std::to_string(this->_selectedPlayer->getLvl());
        this->_selectedPlayerLevelText->setText(levelText);
        std::vector<std::shared_ptr<UIBlocks::IUIBlock>> inventoryTexts;
        std::vector<std::pair<std::shared_ptr<zappyGUI::IRessource>, int>> &inventory = this->_selectedPlayer->getInventory();
        std::vector<std::string> resourceNames = {"Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"};
        for (size_t i = 0; i < inventory.size() && i < resourceNames.size(); ++i) {
            std::string itemText = resourceNames[i] + ": " + std::to_string(inventory[i].second);
            std::shared_ptr<UIBlocks::Text> itemDisplay = std::make_shared<UIBlocks::Text>(itemText, std::pair<float, float>(0, 0), 14);
            inventoryTexts.push_back(itemDisplay);
        }
        for (auto& item : this->_inventoryUI) {
            for (const auto ressource : this->_selectedPlayer->getInventory()) {
                if (ressource.first->getName() == item.first) {
                    item.second.second.setText(std::to_string(ressource.second));
                    break;
                }
            }
        }
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
    for (auto& inventoryItem : this->_inventoryUI) {
        inventoryItem.second.first.draw(window);
        inventoryItem.second.second.draw(window);
    }
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
    if (this->_spellsListUI)
        this->_spellsListUI->handleEvent(event, window);
    if (std::holds_alternative<std::string>(this->_playersListUI->getValue())) {
        std::string selectedPlayerName = std::get<std::string>(this->_playersListUI->getValue());

        for (auto &player : this->_players) {
            if (player.getName() == selectedPlayerName) {
                this->_selectedPlayer = std::make_shared<zappyGUI::Player>(player);
                break;
            }
        }
    }
    for (auto &player: this->_players) {
    }
}

std::shared_ptr<zappyGUI::Player> zappyGUI::Game::getSelectedPlayer()
{
    return _selectedPlayer;
}
