/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pnw.cpp
*/

#include "Pnw.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Pnw::Pnw()
{
}

zappyGUI::Pnw::~Pnw()
{
}

void zappyGUI::Pnw::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    std::pair <int, int> playerPos;
    int orientation;
    int lvl;
    std::string teamName;
    Player newPlayer;

    ss >> code >> playerID >> playerPos.first >> playerPos.second >> orientation >> lvl >> teamName;
    newPlayer.setId(playerID);
    newPlayer.setLvl(lvl);
    newPlayer.setPos(playerPos);
    newPlayer.setName(teamName);
    newPlayer.setOrientation(orientation - 1);
    if (gui.getGame().getPlayers().size() >= playerID)
        gui.getGame().getPlayers().push_back(newPlayer);
    else
        gui.getGame().getPlayers()[playerID] = newPlayer;
    gui.getGame().getMap()[playerPos.first][playerPos.second].addPlayer(std::make_shared <Player> (newPlayer));
    std::clog << "added new player " << playerID << ", lvl " << lvl <<", of the team " << teamName << " in " << newPlayer.getPos().first << " " << playerPos.second << std::endl;
}

void zappyGUI::Pnw::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pnw can not be send by the client");
}
