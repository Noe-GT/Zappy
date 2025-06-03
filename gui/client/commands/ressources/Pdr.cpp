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
    std::stringstream ss(command);
    std::string code;
    int playerID;
    int ressourceID;
    std::pair <int, int> playerPos;

    ss >> code >> playerID >> ressourceID;
    playerPos = gui.getGame().getPlayer(playerID).getPos();
    gui.getGame().getPlayer(playerID).getInventory()[ressourceID].second --;
    // if (gui.getGame().getPlayer(playerID).getInventory()[ressourceID].second < 0)
    //     gui.getGame().getPlayer(playerID).getInventory()[ressourceID].second = 0;
    // else
    //     gui.getGame().getMap()[playerPos.first][playerPos.second].addRessource(gui.getGame().getPlayer(playerID).getInventory()[ressourceID].first);
    std::clog << playerID << " droped " << ressourceID << " in tile " << playerPos.first << " " << playerPos.second << std::endl;
}

void zappyGUI::Pdr::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pdr can not be send by the client");
}
