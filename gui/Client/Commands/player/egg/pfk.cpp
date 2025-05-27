/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pfk.cpp
*/

#include "pfk.hpp"
ZappyGui::pfk::pfk()
{
}

ZappyGui::pfk::~pfk()
{
}

void ZappyGui::pfk::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pfk::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pfk can not be send by the client");
}
