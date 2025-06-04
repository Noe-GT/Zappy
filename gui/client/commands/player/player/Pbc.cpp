/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pbc.cpp
*/

#include "Pbc.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Pbc::Pbc()
{
}

zappyGUI::Pbc::~Pbc()
{
}

void zappyGUI::Pbc::receive(std::string command, zappyGUI::GUI &)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    std::string message;

    ss >> code >> playerID;
    std::getline(ss >> std::ws, message);
    std::clog << "player " << playerID << " sayed: " << message << std::endl;
}

void zappyGUI::Pbc::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pbc can not be send by the client");
}
