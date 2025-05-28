/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Ebw.cpp
*/

#include "Ebw.hpp"
zappyGUI::Ebw::Ebw()
{
}

zappyGUI::Ebw::~Ebw()
{
}

void zappyGUI::Ebw::receive(std::string command, zappyGUI::GUI &gui)
{
    //TODO:
}

void zappyGUI::Ebw::send(std::string command, zappyGUI::GUI &gui)
{
    throw std::runtime_error("Ebw can not be send by the client");
}
