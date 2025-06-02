/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Enw.cpp
*/

#include "Enw.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
zappyGUI::Enw::Enw()
{
}

zappyGUI::Enw::~Enw()
{
}

void zappyGUI::Enw::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Enw::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Enw can not be send by the client");
}
