/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pdi.cpp
*/

#include "pdi.hpp"
ZappyGui::pdi::pdi()
{
}

ZappyGui::pdi::~pdi()
{
}

void ZappyGui::pdi::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pdi::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pdi can not be send by the client");
}
