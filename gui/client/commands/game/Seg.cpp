/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Seg.cpp
*/

#include "Seg.hpp"
zappyGUI::Seg::Seg()
{
}

zappyGUI::Seg::~Seg()
{
}

void zappyGUI::Seg::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Seg::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Seg can not be send by the client");
}
