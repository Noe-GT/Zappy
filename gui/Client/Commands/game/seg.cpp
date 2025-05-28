/*
** EPITECH PROJECT, 2024
** zap
** File description:
** seg.cpp
*/

#include "seg.hpp"
zappyGUI::seg::seg()
{
}

zappyGUI::seg::~seg()
{
}

void zappyGUI::seg::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::seg::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("seg can not be send by the client");
}
