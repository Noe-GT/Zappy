/*
** EPITECH PROJECT, 2024
** zap
** File description:
** ebo.cpp
*/

#include "ebo.hpp"
zappyGUI::ebo::ebo()
{
}

zappyGUI::ebo::~ebo()
{
}

void zappyGUI::ebo::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::ebo::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("ebo can not be send by the client");
}
