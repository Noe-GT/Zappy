/*
** EPITECH PROJECT, 2024
** zap
** File description:
** WELCOME.cpp
*/

#include "WELCOME.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>

zappyGUI::WELCOME::WELCOME()
{
}

zappyGUI::WELCOME::~WELCOME()
{
}

void zappyGUI::WELCOME::receive(std::string, zappyGUI::GUI &gui)
{
    gui.getClient().getCserver().send("GRAPHIC\n");
}

void zappyGUI::WELCOME::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("WELCOME can not be send by the client");
}
