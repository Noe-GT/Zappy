/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pin.cpp
*/

#include "Pin.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Pin::Pin()
{
}

zappyGUI::Pin::~Pin()
{
}

void zappyGUI::Pin::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    int q0;
    int q1;
    int q2;
    int q3;
    int q4;
    int q5;
    int q6;
    int x;
    int y;
    char hash;

    std::clog << "pin" << std::endl;
    ss >> code >> hash >> playerID >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    (void) x;
    (void) y;
    if (playerID < gui.getGame()->getPlayers().size()) {
        gui.getGame()->getPlayers()[playerID].getInventory()[0].second = q0;
        gui.getGame()->getPlayers()[playerID].getInventory()[1].second = q1;
        gui.getGame()->getPlayers()[playerID].getInventory()[2].second = q2;
        gui.getGame()->getPlayers()[playerID].getInventory()[3].second = q3;
        gui.getGame()->getPlayers()[playerID].getInventory()[4].second = q4;
        gui.getGame()->getPlayers()[playerID].getInventory()[5].second = q5;
        gui.getGame()->getPlayers()[playerID].getInventory()[6].second = q6;
        std::clog << "player " << playerID << " have ressources " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " " << q5 << " " << q6 << std::endl;
    }
}

void zappyGUI::Pin::send(std::string command, zappyGUI::GUI &, zappyGUI::Cserver &sender)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    char hash;
    ss >> code >> hash >>playerID;
    sender.send("pin #%d\n", playerID);
}
