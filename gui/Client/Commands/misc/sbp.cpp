/*
** EPITECH PROJECT, 2024
** zap
** File description:
** sbp.cpp
*/

#include "sbp.hpp"
ZappyGui::sbp::sbp()
{
}

ZappyGui::sbp::~sbp()
{
}

void ZappyGui::sbp::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::sbp::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("sbp can not be send by the client");
}
