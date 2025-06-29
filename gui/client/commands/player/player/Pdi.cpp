/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pdi.cpp
*/

#include "Pdi.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Pdi::Pdi()
{
}

zappyGUI::Pdi::~Pdi()
{
}

void zappyGUI::Pdi::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    char hash;
    ss >> code >> hash >> playerID;
    std::clog << "player " << playerID << " is dead" << std::endl;
    if (playerID < 0 || static_cast<size_t>(playerID) < gui.getGame()->getPlayers().size())
        gui.getGame()->getPlayers()[playerID].kill();
}

void zappyGUI::Pdi::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pdi can not be send by the client");
}
