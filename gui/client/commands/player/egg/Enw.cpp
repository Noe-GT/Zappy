/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Enw.cpp
*/

#include "Enw.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Enw::Enw()
{
}

zappyGUI::Enw::~Enw()
{
}

void zappyGUI::Enw::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    int eggID;
    std::pair <int, int> pos;
    Spell spell;
    Player newPlayer;
    char hash;
    char hash2;

    std::clog << "enw" << std::endl;
    ss >> code >> hash >> eggID >> hash2 >> playerID >> pos.first >> pos.second;
    if (playerID >= 0 && static_cast<size_t>(playerID) < gui.getGame()->getPlayers().size()) {
        gui.getGame()->getPlayers()[playerID].getSpellInProgress() = nullptr;
        newPlayer.setName(gui.getGame()->getPlayers()[playerID].getName());
    }
    newPlayer.setId(-1);
    newPlayer.setLvl(0);
    newPlayer.setPos(pos);
    newPlayer.setOrientation(orientation::SOUTH);
    gui.getGame()->getEggs().push_back({std::make_shared <Player> (newPlayer), eggID});
    std::clog << "player " << playerID << " layed an egg (#" << eggID << ") in " << pos.first << " " << pos.second << std::endl;
}

void zappyGUI::Enw::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Enw can not be send by the client");
}
