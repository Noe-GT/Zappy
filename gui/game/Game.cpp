/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "Player.hpp"
#include "../UI/shared/IGraphical.hpp"
#include <regex>

zappyGUI::Game::Game() : _frequence(0), _teamNbr(0), _gameInProgess(false), _mapSize(30, 30), _selectedPlayer(nullptr)
{
    for (size_t y = 0; y < this->_mapSize.second; y++) {
        this->_map.emplace_back();
        for (size_t x = 0; x < this->_mapSize.first; x++)
            this->_map.back().emplace_back(std::pair<size_t, size_t>(x, y));
    }
    
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> emptyList;
    this->_playersListUI = std::make_shared<UIBlocks::PopupSelector>(emptyList, std::pair<float, float>(50, 300), std::pair<float, float>(200, 400));
    this->_selectedPlayerLevelText = std::make_shared<UIBlocks::Text>("Level -1", std::pair<float, float>(700, 30), 24);
    this->_spellsListUI = std::make_shared<UIBlocks::PopupSelector>(emptyList, std::pair<float, float>(1290, 100), std::pair<float, float>(200, 300));
    this->_logsUI = std::make_shared<UIBlocks::PopupSelector>(emptyList, std::pair<float, float>(1290, 500), std::pair<float, float>(200, 400));
    this->_inventoryUI = {
        {"Food", {UIBlocks::Text("Food: ", std::pair<float, float>(50, 30), 16), UIBlocks::Text("0", std::pair<float, float>(150, 30), 16)}},
        {"Linemate", {UIBlocks::Text("Linemate: ", std::pair<float, float>(50, 50), 16), UIBlocks::Text("0", std::pair<float, float>(150, 50), 16)}},
        {"Deraumere", {UIBlocks::Text("Deraumere: ", std::pair<float, float>(50, 70), 16), UIBlocks::Text("0", std::pair<float, float>(150, 70), 16)}},
        {"Sibur", {UIBlocks::Text("Sibur: ", std::pair<float, float>(50, 90), 16), UIBlocks::Text("0", std::pair<float, float>(150, 90), 16)}},
        {"Mendiane", {UIBlocks::Text("Mendiane: ", std::pair<float, float>(50, 110), 16), UIBlocks::Text("0", std::pair<float, float>(150, 110), 16)}},
        {"Phiras", {UIBlocks::Text("Phiras: ", std::pair<float, float>(50, 130), 16), UIBlocks::Text("0", std::pair<float, float>(150, 130), 16)}},
        {"Thystame", {UIBlocks::Text("Thystame: ", std::pair<float, float>(50, 150), 16), UIBlocks::Text("0", std::pair<float, float>(150, 150), 16)}}
    };
    this->_timerUI = std::make_shared<UIBlocks::Timer>(std::pair<float, float>(1290, 30), 24);
    this->_playersListTitle = std::make_shared<UIBlocks::Text>("Players", std::pair<float, float>(110, 270), 24);
    this->_spellsListTitle = std::make_shared<UIBlocks::Text>("Spells", std::pair<float, float>(1355, 70), 24);
    this->_logsTitle = std::make_shared<UIBlocks::Text>("Logs", std::pair<float, float>(1360, 465), 24);
    this->_selectedTileSelector = nullptr;
    this->_timerUI->start();
    this->_playersListUI->open();
    this->_logsUI->open();
    this->_spellsListUI->open();
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
    this->_map.at(0).at(0).addPlayer(std::make_shared<zappyGUI::Player>(player));
    this->_logs.push_back("Game started");
    this->_logs.push_back("1");
    this->_logs.push_back("2");
    this->_logs.push_back("3");
    this->_logs.push_back("4");
    this->_logs.push_back("5");
    this->_logs.push_back("6");
    this->_logs.push_back("7");
    this->_logs.push_back("8");
    this->_logs.push_back("9");
    this->_logs.push_back("10");
    this->_logs.push_back("11");
    this->_logs.push_back("12");
    this->_logs.push_back("13");
    this->_logs.push_back("14");
    this->_logs.push_back("15");
    this->_logs.push_back("16");
    this->_logs.push_back("17");
    this->_logs.push_back("18");
    this->_logs.push_back("19");
    this->_logs.push_back("20");
    this->_logs.push_back("21");
    this->_logs.push_back("22");
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

void zappyGUI::Game::update()
{
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> playerTexts;
    for (size_t i = 0; i < this->_players.size(); ++i) {
        std::string playerInfo = "Player " + std::to_string(this->_players[i].getId()) + " - " + this->_players[i].getName();
        std::shared_ptr<UIBlocks::Text> playerText = std::make_shared<UIBlocks::Text>(playerInfo, std::pair<float, float>(0, 0), 16);
        playerTexts.push_back(playerText);
    }
    this->_playersListUI->setOptions(playerTexts);
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
            for (const auto& ressource : this->_selectedPlayer->getInventory()) {
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
    this->_spellsListUI->setOptions(spellTexts);
    //test
    static int log = 0;
    std::string message = "Hello " + std::to_string(log++);
    this->_logs.push_back(message);
    //
    std::reverse(this->_logs.begin(), this->_logs.end());
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> logTexts;
    for (const auto& log : this->_logs) {
        std::shared_ptr<UIBlocks::Text> logText = std::make_shared<UIBlocks::Text>(log, std::pair<float, float>(0, 0), 14);
        logTexts.push_back(logText);
    }
    this->_logsUI->setOptions(logTexts);
}

void zappyGUI::Game::displayUI(std::shared_ptr<zappyGUI::Window> window)
{
    this->update();
    this->_playersListUI->draw(window);
    this->_selectedPlayerLevelText->draw(window);
    for (auto& inventoryItem : this->_inventoryUI) {
        inventoryItem.second.first.draw(window);
        inventoryItem.second.second.draw(window);
    }
    this->_spellsListUI->draw(window);
    this->_logsUI->draw(window);
    this->_timerUI->draw(window);
    this->_playersListTitle->draw(window);
    this->_spellsListTitle->draw(window);
    this->_logsTitle->draw(window);
    if (this->_selectedTileSelector)
        this->_selectedTileSelector->draw(window);
}

void zappyGUI::Game::handleUIEvents(const sf::Event& event, std::shared_ptr<zappyGUI::Window> window)
{
    if (this->_playersListUI)
        this->_playersListUI->handleEvent(event, window);
    if (this->_selectedPlayerLevelText)
        this->_selectedPlayerLevelText->handleEvent(event, window);
    if (this->_spellsListUI)
        this->_spellsListUI->handleEvent(event, window);
    if (this->_logsUI)
        this->_logsUI->handleEvent(event, window);
    if (this->_selectedTileSelector)
        this->_selectedTileSelector->handleEvent(event, window);

    if (std::holds_alternative<std::string>(this->_playersListUI->getValue())) {
        std::string selectedPlayerName = std::get<std::string>(this->_playersListUI->getValue());
        for (auto &player : this->_players) {
            std::smatch match;
            std::regex regexPattern(R"(Player (\d+) - )");
            if (std::regex_search(selectedPlayerName, match, regexPattern) && match.size() > 1) {
                int playerId = std::stoi(match[1].str());
                if (player.getId() == playerId) {
                    this->_selectedPlayer = std::make_shared<zappyGUI::Player>(player);
                    break;
                }
                continue;
            }
        }
    }
}

void zappyGUI::Game::setSelectedTile(std::pair<float, float> windowPos, std::pair<int, int> mapPos)
{
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> playerTexts;
    for (auto &player: this->_map.at(mapPos.first).at(mapPos.second).getPlayers()) {
        std::string playerInfo = "Player " + std::to_string(player->getId()) + " - " + player->getName();
        std::shared_ptr<UIBlocks::Text> playerText = std::make_shared<UIBlocks::Text>(playerInfo, std::pair<float, float>(0, 0), 16);
        playerTexts.push_back(playerText);
    }
    std::shared_ptr<UIBlocks::PopupSelector> playerSelector = std::make_shared<UIBlocks::PopupSelector>(playerTexts, windowPos, std::pair<float, float>(100, 50));
    std::vector<std::shared_ptr<UIBlocks::Text>> ressourcesTexts;
    for (auto &ressource: this->_map.at(mapPos.first).at(mapPos.second).getRessources()) {
        std::string ressourceInfo = ressource.first->getName() + ": " + std::to_string(ressource.second);
        std::shared_ptr<UIBlocks::Text> ressourceText = std::make_shared<UIBlocks::Text>(ressourceInfo, std::pair<float, float>(0, 0), 16);
        ressourcesTexts.push_back(ressourceText);
    }
    std::shared_ptr<UIBlocks::List> ressourceList = std::make_shared<UIBlocks::List>(ressourcesTexts, windowPos, std::pair<float, float>(100, 50));
    this->_selectedTileSelector->setFirst(playerSelector);
    this->_selectedTileSelector->setSecond(ressourceList);
    this->_selectedTileSelector->setPosition(windowPos);
}


std::shared_ptr<zappyGUI::Player> zappyGUI::Game::getSelectedPlayer()
{
    return _selectedPlayer;
}
