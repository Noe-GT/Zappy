/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pgt.cpp
*/

#include "Pgt.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Pgt::Pgt()
{
}

zappyGUI::Pgt::~Pgt()
{
}

void zappyGUI::Pgt::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    int ressourceID;
    std::pair <int, int> playerPos;

    ss >> code >> playerID >> ressourceID;
    playerPos = gui.getGame().getPlayers()[playerID].getPos();
    gui.getGame().getPlayers()[playerID].getInventory()[ressourceID].second ++;
    // gui.getGame().getMap()[playerPos.first][playerPos.second].getRessource()[ressourceID].second --;
    // if (gui.getGame().getMap()[playerPos.first][playerPos.second].getRessource()[ressourceID].second < 0)
    //     gui.getGame().getMap()[playerPos.first][playerPos.second].getRessource()[ressourceID].second = 0;
    std::clog << "player " << playerID << " harvested " << ressourceID << " in tile " << playerPos.first << " " << playerPos.second << " now have " << gui.getGame().getPlayers()[playerID].getInventory()[ressourceID].second << " left" << std::endl;
}

void zappyGUI::Pgt::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pgt can not be send by the client");
}
