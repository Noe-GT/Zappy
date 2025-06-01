/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pdr.cpp
*/

#include "Pdr.hpp"
zappyGUI::Pdr::Pdr()
{
}

zappyGUI::Pdr::~Pdr()
{
}

void zappyGUI::Pdr::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pdr::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pdr can not be send by the client");
}
