/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Suc.cpp
*/

#include "Suc.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Suc::Suc()
{
}

zappyGUI::Suc::~Suc()
{
}

void zappyGUI::Suc::receive(std::string, zappyGUI::GUI &)
{
    std::clog << "unknow command !" << std::endl;
}

void zappyGUI::Suc::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Suc can not be send by the client");
}
