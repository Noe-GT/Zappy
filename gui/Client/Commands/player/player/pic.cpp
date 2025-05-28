/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pic.cpp
*/

#include "pic.hpp"
zappyGUI::pic::pic()
{
}

zappyGUI::pic::~pic()
{
}

void zappyGUI::pic::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pic::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pic can not be send by the client");
}
