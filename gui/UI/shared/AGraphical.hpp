/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AWorld
*/

#pragma once
#include "IGraphical.hpp"
#include "../../game/Game.hpp"
#include "Window.hpp"

namespace zappyGUI {
    class AGraphical: public IGraphical {
        public:
            // AGraphical();
            AGraphical(zappyGUI::Window &window, zappyGUI::Game &game);
            ~AGraphical() = default;

            virtual void display() override;
            virtual void update() override;
            virtual void handleEvents() override;

        protected:
            zappyGUI::Window &_window;
            const zappyGUI::Game &_game;
    };
}
