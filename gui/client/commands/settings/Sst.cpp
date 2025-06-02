/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Sst.cpp
*/

#include "Sst.hpp"
zappyGUI::Sst::Sst()
{
}

zappyGUI::Sst::~Sst()
{
}

void zappyGUI::Sst::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int newFrequence;

    ss >> code >> newFrequence;
    gui.getGame().setFrequence(newFrequence);
}

void zappyGUI::Sst::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    std::stringstream ss(command);
    std::string code;
    int newFrequence;

    ss >> code >> newFrequence;
    sender.send("sst %d\n", newFrequence);
}
