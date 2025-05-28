/*
** EPITECH PROJECT, 2024
** zap
** File description:
** edi.cpp
*/

#include "edi.hpp"
zappyGUI::edi::edi()
{
}

zappyGUI::edi::~edi()
{
}

void zappyGUI::edi::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::edi::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("edi can not be send by the client");
}
