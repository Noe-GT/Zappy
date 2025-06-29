/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pdr.cpp
*/

#include "Pdr.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Pdr::Pdr()
{
}

zappyGUI::Pdr::~Pdr()
{
}

void zappyGUI::Pdr::receive(std::string command, zappyGUI::GUI &gui)
{
    std::clog << "pdr" << std::endl;
    std::stringstream ss(command);
    std::string code;
    int playerID;
    int ressourceID;
    std::pair <int, int> playerPos;
    char hash;

    ss >> code >> hash >> playerID >> ressourceID;
    playerPos = gui.getGame()->getPlayers()[playerID].getPos();
    std::clog << "pdr1" << std::endl;
    if (playerID >= 0 && static_cast<size_t>(playerID) < gui.getGame()->getPlayers().size()) {
        gui.getGame()->getPlayers()[playerID].getInventory()[ressourceID].second --;
        // if (gui.getGame()->getPlayers()[playerID].getInventory()[ressourceID].second < 0)
        std::clog << "pdr2" << std::endl;
        gui.getGame()->getPlayers()[playerID].getInventory()[ressourceID].second = 0;
        // else
        std::clog << "pdr3" << std::endl;
        gui.getGame()->getMap()[playerPos.second][playerPos.first].getRessources()[ressourceID].second ++;
        std::clog << "player " << playerID << " droped " << ressourceID << " in tile " << playerPos.first << " " << playerPos.second << " now have " << gui.getGame()->getPlayers()[playerID].getInventory()[ressourceID].second << " left" << std::endl;
    }
}

void zappyGUI::Pdr::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pdr can not be send by the client");
}
