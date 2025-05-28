/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Suc.cpp
*/

#include "Suc.hpp"
zappyGUI::Suc::Suc()
{
}

zappyGUI::Suc::~Suc()
{
}

void zappyGUI::Suc::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Suc::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Suc can not be send by the client");
}
