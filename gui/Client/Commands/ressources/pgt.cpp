/*
** EPITECH PROJECT, 2024
** zap
** File description:
** pgt.cpp
*/

#include "pgt.hpp"
ZappyGui::pgt::pgt()
{
}

ZappyGui::pgt::~pgt()
{
}

void ZappyGui::pgt::receive(std::string command, ZappyGui::GUI &gui)
{
    //TODO:
}

void ZappyGui::pgt::send(std::string command, ZappyGui::GUI &gui)
{
    throw std::runtime_error("pgt can not be send by the client");
}
