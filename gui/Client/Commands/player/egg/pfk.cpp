/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pfk.cpp
*/

#include "pfk.hpp"
zappyGUI::pfk::pfk()
{
}

zappyGUI::pfk::~pfk()
{
}

void zappyGUI::pfk::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pfk::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pfk can not be send by the client");
}
