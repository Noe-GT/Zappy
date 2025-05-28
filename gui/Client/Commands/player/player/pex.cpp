/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pex.cpp
*/

#include "pex.hpp"
zappyGUI::pex::pex()
{
}

zappyGUI::pex::~pex()
{
}

void zappyGUI::pex::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pex::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pex can not be send by the client");
}
