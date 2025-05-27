/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pex.cpp
*/

#include "pex.hpp"
ZappyGui::pex::pex()
{
}

ZappyGui::pex::~pex()
{
}

void ZappyGui::pex::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pex::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pex can not be send by the client");
}
