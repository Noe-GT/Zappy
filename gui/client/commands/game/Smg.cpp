/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Smg.cpp
*/

#include "Smg.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Smg::Smg()
{
}

zappyGUI::Smg::~Smg()
{
}

void zappyGUI::Smg::receive(std::string command, zappyGUI::GUI &gui)
{
    command.erase(0, 4);
    gui.getGame()->getLogs().push_back(command);
    std::clog << "server message receive: " << command << std::endl;
}

void zappyGUI::Smg::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Smg can not be send by the client");
}
