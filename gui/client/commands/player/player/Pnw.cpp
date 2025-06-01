/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pnw.cpp
*/

#include "Pnw.hpp"
zappyGUI::Pnw::Pnw()
{
}

zappyGUI::Pnw::~Pnw()
{
}

void zappyGUI::Pnw::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pnw::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pnw can not be send by the client");
}
