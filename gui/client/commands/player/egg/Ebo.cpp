/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Ebo.cpp
*/

#include "Ebo.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
zappyGUI::Ebo::Ebo()
{
}

zappyGUI::Ebo::~Ebo()
{
}

void zappyGUI::Ebo::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Ebo::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Ebo can not be send by the client");
}
