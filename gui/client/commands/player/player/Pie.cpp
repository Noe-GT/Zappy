/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pie.cpp
*/

#include "Pie.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Pie::Pie()
{
}

zappyGUI::Pie::~Pie()
{
}

void zappyGUI::Pie::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int x;
    int y;
    int sucessStatus;

    ss >> code >> x >> y >> sucessStatus;
    for (std::size_t i = 0; i != gui.getGame()->getMap()[y][x].getPlayers().size(); i++) {
        if (gui.getGame()->getMap()[y][x].getPlayers()[i]->getSpellInProgress() != nullptr) {
            gui.getGame()->getMap()[y][x].getPlayers()[i]->getSpellInProgress() = nullptr;
            gui.getGame()->getMap()[y][x].getPlayers()[i]->setLastSpellSucess(sucessStatus);
            std::clog << "the spell of the player " << gui.getGame()->getMap()[y][x].getPlayers()[i]->getId() << " finished with status " << sucessStatus << std::endl;
            gui.getClient().getCserver().send("plv %d\n", i);
        }
    }
}

void zappyGUI::Pie::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pie can not be send by the client");
}
