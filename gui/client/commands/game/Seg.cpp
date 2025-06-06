/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Seg.cpp
*/

#include "Seg.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Seg::Seg()
{
}

zappyGUI::Seg::~Seg()
{
}

void zappyGUI::Seg::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    std::string teamName;

    ss >> code >> teamName;
    gui.getWindow()->close();
    std::clog << "end of the game team " << teamName << " won" << std::endl;
}

void zappyGUI::Seg::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Seg can not be send by the client");
}
