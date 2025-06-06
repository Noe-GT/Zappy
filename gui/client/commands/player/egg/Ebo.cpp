/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Ebo.cpp
*/

#include "Ebo.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Ebo::Ebo()
{
}

zappyGUI::Ebo::~Ebo()
{
}

void zappyGUI::Ebo::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int eggID;

    ss >> code >> eggID;
    auto it = std::find_if(gui.getGame()->getEggs().begin(), gui.getGame()->getEggs().end(), [eggID](const auto& egg) {
        return egg.second == eggID;
    });
    if (it != gui.getGame()->getEggs().end()) {
        gui.getGame()->getEggs().erase(it);
        std::clog << "a player is born from egg " << eggID << std::endl;
    }
}

void zappyGUI::Ebo::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Ebo can not be send by the client");
}
