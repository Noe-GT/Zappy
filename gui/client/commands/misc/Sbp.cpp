/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sbp.cpp
*/

#include "Sbp.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Sbp::Sbp()
{
}

zappyGUI::Sbp::~Sbp()
{
}

void zappyGUI::Sbp::receive(std::string, zappyGUI::GUI &)
{
    std::clog << "wrong parameter !" << std::endl;
}

void zappyGUI::Sbp::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Sbp can not be send by the client");
}
