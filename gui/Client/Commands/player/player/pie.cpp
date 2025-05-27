/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pie.cpp
*/

#include "pie.hpp"
ZappyGui::pie::pie()
{
}

ZappyGui::pie::~pie()
{
}

void ZappyGui::pie::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pie::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pie can not be send by the client");
}
