/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pic.cpp
*/

#include "Pic.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>

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
    int casterID;
    int playerID;
    Spell spell;

    ss >> code >> x >> y >> lvl >> casterID;
    spell.setLevel(gui.getGame()->getPlayers()[casterID].getLvl() + 1);
    spell.setCaster(std::make_shared <Player> (gui.getGame()->getPlayers()[casterID]));
    spell.setPos(x, y);
    spell.resetStartTime();
    gui.getGame()->getMap()[x][y].getPlayers()[casterID]->setSpellInProgress(std::make_shared <Spell> (spell));
    std::clog << "a new incentation start in " << x << " " << y << " to reach lvl " << spell.getLevel() << " initiated by player " << casterID << std::endl;

    while (ss >> playerID) {
        spell.getParticipant().push_back(std::make_shared <Player> (gui.getGame()->getPlayers()[playerID]));
        gui.getGame()->getMap()[x][y].getPlayers()[playerID]->setSpellInProgress(std::make_shared <Spell> (spell));
        std::clog << "    player " << playerID << " take part of it !" << std::endl;
    }
}

void zappyGUI::Pic::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pic can not be send by the client");
}
