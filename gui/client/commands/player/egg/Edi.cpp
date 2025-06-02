/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Edi.cpp
*/

#include "Edi.hpp"
zappyGUI::Edi::Edi()
{
}

zappyGUI::Edi::~Edi()
{
}

void zappyGUI::Edi::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Edi::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Edi can not be send by the client");
}
