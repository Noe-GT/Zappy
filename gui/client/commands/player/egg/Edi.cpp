/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Edi.cpp
*/

#include "Edi.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Edi::Edi()
{
}

zappyGUI::Edi::~Edi()
{
}

void zappyGUI::Edi::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int eggID;

    ss >> code >> eggID;
    auto it = std::find_if(gui.getGame().getEggs().begin(), gui.getGame().getEggs().end(), [eggID](const auto& egg) {
        return egg.second == eggID;
    });
    if (it != gui.getGame().getEggs().end()) {
        gui.getGame().getEggs().erase(it);
        std::clog << "egg " << eggID << " has been destroyed" << std::endl;
    }
}

void zappyGUI::Edi::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Edi can not be send by the client");
}
