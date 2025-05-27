/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pbc.cpp
*/

#include "pbc.hpp"
ZappyGui::pbc::pbc()
{
}

ZappyGui::pbc::~pbc()
{
}

void ZappyGui::pbc::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pbc::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pbc can not be send by the client");
}
