/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pic.cpp
*/

#include "Pic.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
zappyGUI::Pic::Pic()
{
}

zappyGUI::Pic::~Pic()
{
}

void zappyGUI::Pic::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pic::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pic can not be send by the client");
}
