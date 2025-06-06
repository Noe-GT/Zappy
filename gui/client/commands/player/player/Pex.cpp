/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pex.cpp
*/

#include "Pex.hpp"
#include "../../../../GUI.hpp"
#include "../../../Cserver.hpp"
#include <iostream>
zappyGUI::Pex::Pex()
{
}

zappyGUI::Pex::~Pex()
{
}

std::vector <int> getPlayerToMove(zappyGUI::Game &game, int id)
{
    std::pair <int, int> pos;
    std::vector <int> result;

    pos.first = game.getPlayers()[id].getPos().first;
    pos.second = game.getPlayers()[id].getPos().second;
    if (game.getPlayers()[id].getOrientation() == zappyGUI::orientation::NORTH) {
        pos.second --;
        if (pos.second < 0)
            pos.second = game.getMap().size() - 1;
    }
    if (game.getPlayers()[id].getOrientation() == zappyGUI::orientation::SOUTH) {
        pos.second ++;
        if (pos.second > (int)game.getMap().size() - 1)
            pos.second = 0;
    }
    if (game.getPlayers()[id].getOrientation() == zappyGUI::orientation::WEST) {
        pos.first --;
        if (pos.first < 0)
            pos.first = game.getMap()[0].size() - 1;
    }
    if (game.getPlayers()[id].getOrientation() == zappyGUI::orientation::EAST) {
        pos.first ++;
        if (pos.first > (int)game.getMap()[0].size() - 1)
            pos.first = 0;
    }
    std::clog << pos.first << " " << pos.second << std::endl;
    for (std::size_t i = 0; i != game.getMap()[pos.first][pos.second].getPlayers().size(); i++) {
        if (game.getMap()[pos.first][pos.second].getPlayers()[i]->getLvl() != 0) {
            if (!game.getMap()[pos.first][pos.second].getPlayers()[i]->isAlive()) {
                result.push_back(game.getMap()[pos.first][pos.second].getPlayers()[i]->getId());
            }
        }
    }
    return result;
}

void zappyGUI::Pex::receive(std::string command, zappyGUI::GUI &gui)
{
    std::stringstream ss(command);
    std::string code;
    int playerID;
    std::vector <int> playerToMove;

    ss >> code >> playerID;
    playerToMove = getPlayerToMove(gui.getGame(), playerID);
    for (std::size_t i = 0; i != playerToMove.size(); i++) {
        std::clog << "player " << playerID << " expulsed player " << playerToMove[i] << std::endl;
        gui.getClient().getCserver().send("ppo %d\n", playerToMove[i]);
    }
}

void zappyGUI::Pex::send(std::string, zappyGUI::GUI &, zappyGUI::Cserver &)
{
    throw std::runtime_error("Pex can not be send by the client");
}
