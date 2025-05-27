/*
** EPITECH PROJECT, 2024
** zap
** File description:
** smg.cpp
*/

#include "smg.hpp"
ZappyGui::smg::smg()
{
}

ZappyGui::smg::~smg()
{
}

void ZappyGui::smg::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::smg::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("smg can not be send by the client");
}
