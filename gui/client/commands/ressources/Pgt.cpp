/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pgt.cpp
*/

#include "Pgt.hpp"
zappyGUI::Pgt::Pgt()
{
}

zappyGUI::Pgt::~Pgt()
{
}

void zappyGUI::Pgt::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pgt::send(std::string command, zappyGUI::GUI &gui, zappyGUI::Cserver &sender)
{
    throw std::runtime_error("Pgt can not be send by the client");
}
