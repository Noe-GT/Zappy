/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pbc.cpp
*/

#include "pbc.hpp"
zappyGUI::pbc::pbc()
{
}

zappyGUI::pbc::~pbc()
{
}

void zappyGUI::pbc::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pbc::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pbc can not be send by the client");
}
