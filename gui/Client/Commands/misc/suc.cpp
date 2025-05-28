/*
** EPITECH PROJECT, 2024
** zap
** File description:
** suc.cpp
*/

#include "suc.hpp"
zappyGUI::suc::suc()
{
}

zappyGUI::suc::~suc()
{
}

void zappyGUI::suc::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::suc::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("suc can not be send by the client");
}
