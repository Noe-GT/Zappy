/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pbc.cpp
*/

#include "Pbc.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
zappyGUI::Pbc::Pbc()
{
}

zappyGUI::Pbc::~Pbc()
{
}

void zappyGUI::Pbc::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pbc::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pbc can not be send by the client");
}
