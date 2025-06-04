/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Msz.cpp
*/

#include "Msz.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
zappyGUI::Msz::Msz()
{
}

zappyGUI::Msz::~Msz()
{
}

void zappyGUI::Msz::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int x;
    int y;

    ss >> code >> x >> y;
    gui.getGame().setMapSize(x, y);
}

void zappyGUI::Msz::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &sender)
{
    sender.send("msz\n");
}
