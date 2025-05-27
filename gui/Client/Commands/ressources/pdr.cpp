/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pdr.cpp
*/

#include "pdr.hpp"
ZappyGui::pdr::pdr()
{
}

ZappyGui::pdr::~pdr()
{
}

void ZappyGui::pdr::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pdr::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pdr can not be send by the client");
}
