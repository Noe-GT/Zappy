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

void zappyGUI::Mct::receive(std::string, zappyGUI::GUI &)
{
    throw std::runtime_error("Mtc can not be receive by the client");
}

void zappyGUI::Mct::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &sender)
{
    sender.send("mct\n");
}
