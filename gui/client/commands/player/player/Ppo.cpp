/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Ppo.cpp
*/

#include "Ppo.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Ppo::Ppo()
{
}

zappyGUI::Ppo::~Ppo()
{
}
void zappyGUI::Ppo::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    std::pair<int, int> pos;
    std::pair<int, int> oldPos;
    int orientation;
    char hash;

    std::clog << "ppo" << std::endl;
    ss >> code >> hash >> playerID >> pos.first >> pos.second >> orientation;
    if (playerID > 0 && static_cast<size_t>(playerID) > gui.getGame()->getPlayers().size())
        return;
    oldPos = gui.getGame()->getPlayers()[playerID].getPos();
    gui.getGame()->getMap()[oldPos.second][oldPos.first].removePlayerAt(playerID);
    std::vector<std::shared_ptr<zappyGUI::Player>>& playersOnTile = gui.getGame()->getMap()[oldPos.second][oldPos.first].getPlayers();
    auto it = std::find_if(playersOnTile.begin(), playersOnTile.end(), [playerID](const auto& player) {
        return player->getId() == playerID;
    });
    if (it != playersOnTile.end())
        playersOnTile.erase(it);
    gui.getGame()->getMap()[pos.second][pos.first].addPlayer(std::make_shared <Player> (gui.getGame()->getPlayers()[playerID]));
    gui.getGame()->getPlayers()[playerID].setOrientation(orientation - 1);
    gui.getGame()->getPlayers()[playerID].setPos(pos);
    std::clog << "player " << playerID << " moved to " << pos.first << " " << pos.second << " with orientation to " << orientation << std::endl;
}

void zappyGUI::Ppo::send(std::string command, zappyGUI::GUI &, zappyGUI::Cserver &sender)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    char hash;
    ss >> code >> hash >> playerID;
    sender.send("ppo #%d\n", playerID);
}
