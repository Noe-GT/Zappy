/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pgt.cpp
*/

#include "pgt.hpp"
zappyGUI::pgt::pgt()
{
}

zappyGUI::pgt::~pgt()
{
}

void zappyGUI::pgt::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::pgt::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("pgt can not be send by the client");
}
