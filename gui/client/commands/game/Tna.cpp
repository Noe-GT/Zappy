/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tna.cpp
*/

#include "Tna.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Tna::Tna()
{
}

zappyGUI::Tna::~Tna()
{
}

void zappyGUI::Tna::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    std::string teamName;

    ss >> code >> teamName;
    std::clog << "added team " << teamName << ", now have " << gui.getGame()->getTeams().size() << " teams registered" << std::endl;
    gui.getGame()->addTeam(teamName);
}

void zappyGUI::Tna::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &sender)
{
    sender.send("tna\n");
}
