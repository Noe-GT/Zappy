/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Mct.cpp
*/

#include "Mct.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Mct::Mct()
{
}

zappyGUI::Mct::~Mct()
{
}

void zappyGUI::Mct::receive(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Mtc can not be receive by the client");
}

void zappyGUI::Mct::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    sender.send("mct\n");
}
