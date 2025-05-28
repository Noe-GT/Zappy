/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Smg.cpp
*/

#include "Smg.hpp"
zappyGUI::Smg::Smg()
{
}

zappyGUI::Smg::~Smg()
{
}

void zappyGUI::Smg::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Smg::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Smg can not be send by the client");
}
