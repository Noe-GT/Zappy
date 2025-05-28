/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pie.cpp
*/

#include "Pie.hpp"
zappyGUI::Pie::Pie()
{
}

zappyGUI::Pie::~Pie()
{
}

void zappyGUI::Pie::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pie::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Pie can not be send by the client");
}
