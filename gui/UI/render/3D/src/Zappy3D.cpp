/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy3D.cpp
*/

#include "Zappy3D.hpp"

zappyGUI::Zappy3D::Zappy3D()
{
}

void zappyGUI::Zappy3D::display()
{
}

void zappyGUI::Zappy3D::update()
{
    // (void)tile;
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy3D();
    }
}
