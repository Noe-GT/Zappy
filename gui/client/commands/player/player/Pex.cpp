/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pex.cpp
*/

#include "Pex.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
zappyGUI::Pex::Pex()
{
}

zappyGUI::Pex::~Pex()
{
}

void zappyGUI::Pex::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pex::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pex can not be send by the client");
}
