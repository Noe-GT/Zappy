/*
** EPITECH PROJECT, 2024
** zap
** File description:
** enw.cpp
*/

#include "enw.hpp"
ZappyGui::enw::enw()
{
}

ZappyGui::enw::~enw()
{
}

void ZappyGui::enw::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::enw::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("enw can not be send by the client");
}
