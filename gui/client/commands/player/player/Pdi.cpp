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
    gui.getGame()->getPlayers()[playerID].kill();
    std::clog << "player " << playerID << " is dead" << std::endl;
}

void zappyGUI::Pdi::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pdi can not be send by the client");
}
