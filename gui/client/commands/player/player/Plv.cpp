/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Plv.cpp
*/

#include "Plv.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Plv::Plv()
{
}

zappyGUI::Plv::~Plv()
{
}

void zappyGUI::Plv::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    int lvl;
    char hash;
    ss >> code >> hash >> playerID >> lvl;
    if (playerID < 0 || static_cast<size_t>(playerID) < gui.getGame()->getPlayers().size()) {
        gui.getGame()->getPlayers()[playerID].setLvl(lvl);
        std::clog << "player " << playerID << " is lvl " << lvl << std::endl;
    }
}

void zappyGUI::Plv::send(std::string command, zappyGUI::GUI &, zappyGUI::Cserver &sender)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;

    std::clog << "pin" << std::endl;
    ss >> code >> playerID;
    sender.send("plv %d\n", playerID);
}
