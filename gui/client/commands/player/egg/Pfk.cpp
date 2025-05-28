/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Pfk.cpp
*/

#include "Pfk.hpp"
zappyGUI::Pfk::Pfk()
{
}

zappyGUI::Pfk::~Pfk()
{
}

void zappyGUI::Pfk::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Pfk::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Pfk can not be send by the client");
}
