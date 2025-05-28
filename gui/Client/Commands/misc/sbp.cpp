/*
** EPITECH PROJECT, 2024
** zap
** File description:
** sbp.cpp
*/

#include "sbp.hpp"
zappyGUI::sbp::sbp()
{
}

zappyGUI::sbp::~sbp()
{
}

void zappyGUI::sbp::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::sbp::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("sbp can not be send by the client");
}
