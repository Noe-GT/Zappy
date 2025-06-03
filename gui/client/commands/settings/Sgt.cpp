/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sgt.cpp
*/

#include "Sgt.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Sgt::Sgt()
{
}

zappyGUI::Sgt::~Sgt()
{
}

void zappyGUI::Sgt::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int newFrequence;

    ss >> code >> newFrequence;
    gui.getGame().setFrequence(newFrequence);
    std::clog << "newFrequence set to " << newFrequence << std::endl;
}

void zappyGUI::Sgt::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    sender.send("sgt\n");
}
