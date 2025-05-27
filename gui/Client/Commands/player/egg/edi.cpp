/*
** EPITECH PROJECT, 2024
** zap
** File description:
** edi.cpp
*/

#include "edi.hpp"
ZappyGui::edi::edi()
{
}

ZappyGui::edi::~edi()
{
}

void ZappyGui::edi::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::edi::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("edi can not be send by the client");
}
