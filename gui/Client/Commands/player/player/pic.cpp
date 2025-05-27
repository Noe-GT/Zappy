/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pic.cpp
*/

#include "pic.hpp"
ZappyGui::pic::pic()
{
}

ZappyGui::pic::~pic()
{
}

void ZappyGui::pic::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pic::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pic can not be send by the client");
}
