/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pfk.cpp
*/

#include "Pfk.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Pfk::Pfk()
{
}

zappyGUI::Pfk::~Pfk()
{
}

void zappyGUI::Pfk::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    std::pair <int, int> pos;
    Spell spell;

    ss >> code >> playerID;
    pos = gui.getGame()->getPlayers()[playerID].getPos();
    spell.setLevel(-1);
    spell.setCaster(std::make_shared <Player> (gui.getGame()->getPlayers()[playerID]));
    spell.resetStartTime();
    gui.getGame()->getPlayers()[playerID].getSpellInProgress() = std::make_shared <Spell> (spell);
    std::clog << "player " << playerID << " started to lay an egg in " << pos.first << " " << pos.second << std::endl;
}

void zappyGUI::Pfk::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pfk can not be send by the client");
}
