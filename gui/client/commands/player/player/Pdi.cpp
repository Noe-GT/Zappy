/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pdi.cpp
*/

#include "Pdi.hpp"
zappyGUI::Pdi::Pdi()
{
}

zappyGUI::Pdi::~Pdi()
{
}

void zappyGUI::Pdi::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pdi::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Pdi can not be send by the client");
}
