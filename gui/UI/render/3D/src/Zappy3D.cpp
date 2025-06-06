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

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy3D();
    }
}
