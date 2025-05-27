/*
** EPITECH PROJECT, 2024
** zap
** File description:
** seg.cpp
*/

#include "seg.hpp"
ZappyGui::seg::seg()
{
}

ZappyGui::seg::~seg()
{
}

void ZappyGui::seg::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::seg::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("seg can not be send by the client");
}
