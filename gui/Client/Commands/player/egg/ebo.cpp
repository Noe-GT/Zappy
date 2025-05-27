/*
** EPITECH PROJECT, 2024
** zap
** File description:
** ebo.cpp
*/

#include "ebo.hpp"
ZappyGui::ebo::ebo()
{
}

ZappyGui::ebo::~ebo()
{
}

void ZappyGui::ebo::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::ebo::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("ebo can not be send by the client");
}
