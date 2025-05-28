/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pdi.cpp
*/

#include "pdi.hpp"
zappyGUI::pdi::pdi()
{
}

zappyGUI::pdi::~pdi()
{
}

void zappyGUI::pdi::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pdi::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pdi can not be send by the client");
}
