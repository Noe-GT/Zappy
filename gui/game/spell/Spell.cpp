/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Spell.cpp
*/

#include "Spell.hpp"

zappyGUI::Spell::Spell(): _lvl(0), _startTime(std::time(nullptr))
{

}

zappyGUI::Spell::~Spell()
{

}

int zappyGUI::Spell::getLevel()
{
    return this->_lvl;
}

std::time_t zappyGUI::Spell::getStartTime()
{
    return this->_startTime;
}

std::shared_ptr<zappyGUI::Player> zappyGUI::Spell::getCaster()
{
    return this->_caster;
}

std::pair <int, int> zappyGUI::Spell::getPos()
{
    return this->_pos;
}

double zappyGUI::Spell::getSpendedTime()
{
    return std::difftime(std::time(nullptr), this->_startTime);
}

std::vector<std::shared_ptr<zappyGUI::Player>> &zappyGUI::Spell::getParticipant()
{
    return this->_participant;
}

void zappyGUI::Spell::setLevel(int newVal)
{
    this->_lvl = newVal;
}

void zappyGUI::Spell::setStartTime(std::time_t newVal)
{
    this->_startTime = newVal;
}

void zappyGUI::Spell::resetStartTime()
{
    this->_startTime = std::time(nullptr);
}

void zappyGUI::Spell::setCaster(std::shared_ptr<zappyGUI::Player> newVal)
{
    this->_caster = newVal;
}

void zappyGUI::Spell::setPos(int newX, int newY)
{
    this->_pos = {newX, newY};
}

void zappyGUI::Spell::setParticipant(std::vector<std::shared_ptr<zappyGUI::Player>> newVal)
{
    this->_participant = newVal;
}
