/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "ressources/Food.hpp"
#include "ressources/Linemate.hpp"
#include "ressources/Deraumere.hpp"
#include "ressources/Sibur.hpp"
#include "ressources/Mendiane.hpp"
#include "ressources/Phiras.hpp"
#include "ressources/Thystame.hpp"

zappyGUI::Player::Player(): _lastspellSucess(false), _spellInProgress(nullptr)
{
    this->_inventory.push_back({std::make_shared<Food> (),0});
    this->_inventory.push_back({std::make_shared<Linemate> (),0});
    this->_inventory.push_back({std::make_shared<Deraumere> (),0});
    this->_inventory.push_back({std::make_shared<Sibur> (),0});
    this->_inventory.push_back({std::make_shared<Mendiane> (),0});
    this->_inventory.push_back({std::make_shared<Phiras> (),0});
    this->_inventory.push_back({std::make_shared<Thystame> (),0});
}

zappyGUI::Player::~Player()
{
}

zappyGUI::Player::Player(const zappyGUI::Player& other):
    _id(other._id),
    _lvl(other._lvl),
    _pos(other._pos),
    _name(other._name),
    _orientation(other._orientation),
    _inventory(other._inventory),
    _spellInProgress(other._spellInProgress),
    _visionData(other._visionData),
    _logs(other._logs)
{
}

int zappyGUI::Player::getId()
{
    return this->_id;
}

int zappyGUI::Player::getLvl()
{
    return this->_lvl;
}

std::string zappyGUI::Player::getName()
{
    return this->_name;
}

std::vector <std::pair <std::shared_ptr <zappyGUI::IRessource>, int>> &zappyGUI::Player::getInventory()
{
    return this->_inventory;
}

std::shared_ptr <zappyGUI::ISpell> &zappyGUI::Player::getSpellInProgress()
{
    return this->_spellInProgress;
}

std::vector <zappyGUI::Tile> &zappyGUI::Player::getVisionData()
{
    return this->_visionData;
}

std::vector <std::string> &zappyGUI::Player::getLogs()
{
    return this->_logs;
}

std::pair <int, int> zappyGUI::Player::getPos()
{
    return this->_pos;
}

zappyGUI::orientation zappyGUI::Player::getOrientation()
{
    return this->_orientation;
}

bool zappyGUI::Player::isLastSpellSucess()
{
    return this->_lastspellSucess;
}

void zappyGUI::Player::setId(int newVal)
{
    this->_id = newVal;
}

void zappyGUI::Player::setLvl(int newVal)
{
    this->_lvl = newVal;
}

void zappyGUI::Player::setName(std::string newVal)
{
    this->_name = newVal;
}

void zappyGUI::Player::setInventory(std::vector <std::pair <std::shared_ptr <zappyGUI::IRessource>, int>> newVal)
{
    this->_inventory = newVal;
}

void zappyGUI::Player::setSpellInProgress(std::shared_ptr <zappyGUI::ISpell> newVal)
{
    this->_spellInProgress = newVal;
}

void zappyGUI::Player::setVisionData(std::vector <zappyGUI::Tile> newVal)
{
    this->_visionData = newVal;
}

void zappyGUI::Player::setLogs(std::vector <std::string> newVal)
{
    this->_logs = newVal;
}

void zappyGUI::Player::setPos(std::pair <int, int> newVal)
{
    this->_pos = newVal;
}
void zappyGUI::Player::setOrientation(int newVal)
{
    this->_orientation = orientation(newVal);
}

void zappyGUI::Player::setLastSpellSucess(bool newVal)
{
    this->_lastspellSucess = newVal;
}

