/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy2D.cpp
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D()
{
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy2D();
    }
}
