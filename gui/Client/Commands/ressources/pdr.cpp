/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pdr.cpp
*/

#include "pdr.hpp"
zappyGUI::pdr::pdr()
{
}

zappyGUI::pdr::~pdr()
{
}

void zappyGUI::pdr::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pdr::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pdr can not be send by the client");
}
