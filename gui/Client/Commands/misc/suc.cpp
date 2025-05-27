/*
** EPITECH PROJECT, 2024
** zap
** File description:
** suc.cpp
*/

#include "suc.hpp"
ZappyGui::suc::suc()
{
}

ZappyGui::suc::~suc()
{
}

void ZappyGui::suc::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::suc::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("suc can not be send by the client");
}
