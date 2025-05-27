/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pnw.cpp
*/

#include "pnw.hpp"
ZappyGui::pnw::pnw()
{
}

ZappyGui::pnw::~pnw()
{
}

void ZappyGui::pnw::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pnw::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pnw can not be send by the client");
}
