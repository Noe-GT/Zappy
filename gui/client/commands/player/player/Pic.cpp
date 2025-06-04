/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pic.cpp
*/

#include "Pic.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
zappyGUI::Pic::Pic()
{
}

zappyGUI::Pic::~Pic()
{
}

void zappyGUI::Pic::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int x;
    int y;
    int lvl;
    int playerID;

    ss >> code >> x >> y >> lvl >> playerID;
    gui.getGame().getMap()[x][y].getPlayers()[playerID]->getSpellInProgress();
}

void zappyGUI::Pic::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pic can not be send by the client");
}
