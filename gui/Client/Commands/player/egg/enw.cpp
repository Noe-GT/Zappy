/*
** EPITECH PROJECT, 2024
** zap
** File description:
** enw.cpp
*/

#include "enw.hpp"
zappyGUI::enw::enw()
{
}

zappyGUI::enw::~enw()
{
}

void zappyGUI::enw::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::enw::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("enw can not be send by the client");
}
