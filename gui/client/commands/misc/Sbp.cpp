/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sbp.cpp
*/

#include "Sbp.hpp"
zappyGUI::Sbp::Sbp()
{
}

zappyGUI::Sbp::~Sbp()
{
}

void zappyGUI::Sbp::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Sbp::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Sbp can not be send by the client");
}
