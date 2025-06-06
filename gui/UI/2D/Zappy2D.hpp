/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Zappy2D
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "UI/shared/Window.hpp"
#include "UI/shared/AGraphical.hpp"

namespace zappyGUI {
    class Zappy2D: public zappyGUI::AGraphical {
        public:
            Zappy2D(zappyGUI::Window &window, zappyGUI::Game &game);
            ~Zappy2D() = default;

            void display() final;
            void update() final;
            void handleEvents() final;
        private:
    };
}

