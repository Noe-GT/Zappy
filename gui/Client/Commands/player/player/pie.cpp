/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pie.cpp
*/

#include "pie.hpp"
zappyGUI::pie::pie()
{
}

zappyGUI::pie::~pie()
{
}

void zappyGUI::pie::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pie::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pie can not be send by the client");
}
