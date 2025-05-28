/*
** EPITECH PROJECT, 2024
** zap
** File description:
** smg.cpp
*/

#include "smg.hpp"
zappyGUI::smg::smg()
{
}

zappyGUI::smg::~smg()
{
}

void zappyGUI::smg::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::smg::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("smg can not be send by the client");
}
