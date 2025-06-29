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
    char hash;

    std::clog << "pic" << std::endl;
    ss >> code >> x >> y >> lvl >> hash >> casterID;
    if (casterID >= gui.getGame()->getPlayers().size()) {
        return;
    }
    spell.setLevel(gui.getGame()->getPlayers()[casterID].getLvl() + 1);
    spell.setCaster(std::make_shared <Player> (gui.getGame()->getPlayers()[casterID]));
    spell.setPos(x, y);
    spell.resetStartTime();
    gui.getGame()->getPlayers()[casterID].setSpellInProgress(std::make_shared <Spell> (spell));
    // gui.getGame()->getMap()[y][x].getPlayers()[casterID]->setSpellInProgress(std::make_shared <Spell> (spell));
    std::clog << "a new incentation start in " << x << " " << y << " to reach lvl " << spell.getLevel() << " initiated by player " << casterID << std::endl;

    while (ss >> hash >> playerID) {
        spell.getParticipant().push_back(std::make_shared <Player> (gui.getGame()->getPlayers()[playerID]));
        gui.getGame()->getPlayers()[casterID].setSpellInProgress(std::make_shared <Spell> (spell));
        // gui.getGame()->getMap()[y][x].getPlayers()[playerID]->setSpellInProgress(std::make_shared <Spell> (spell));
        std::clog << "    player " << playerID << " take part of it !" << std::endl;
    }
}

void zappyGUI::Pic::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pic can not be send by the client");
}
