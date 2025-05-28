/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pnw.cpp
*/

#include "pnw.hpp"
zappyGUI::pnw::pnw()
{
}

zappyGUI::pnw::~pnw()
{
}

void zappyGUI::pnw::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pnw::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pnw can not be send by the client");
}
