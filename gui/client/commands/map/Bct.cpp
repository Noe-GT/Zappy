/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Bct.cpp
*/

#include "Bct.hpp"
#include "../../../GUI.hpp"
#include "../../Cserver.hpp"
#include <iostream>
zappyGUI::Bct::Bct()
{
}

zappyGUI::Bct::~Bct()
{
}

void zappyGUI::Bct::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int x;
    int y;
    int q0;
    int q1;
    int q2;
    int q3;
    int q4;
    int q5;
    int q6;

    ss >> code >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    gui.getGame()->getMap()[x][y].getRessources()[0].second = q0;
    gui.getGame()->getMap()[x][y].getRessources()[1].second = q1;
    gui.getGame()->getMap()[x][y].getRessources()[2].second = q2;
    gui.getGame()->getMap()[x][y].getRessources()[3].second = q3;
    gui.getGame()->getMap()[x][y].getRessources()[4].second = q4;
    gui.getGame()->getMap()[x][y].getRessources()[5].second = q5;
    gui.getGame()->getMap()[x][y].getRessources()[6].second = q6;
    std::clog << "tile " << x << " " << y << " have ressources " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " " << q5 << " " << q6 << ", and " << gui.getGame()->getMap()[x][y].getPlayers().size() << " players" << std::endl;
}

void zappyGUI::Bct::send(std::string command, zappyGUI::GUI &, zappyGUI::Cserver &sender)
{
    std::stringstream ss(command);
    std::string code;
    int x;
    int y;

    ss >> code >> x >> y;
    sender.send("bct %d %d\n", x, y);
}
