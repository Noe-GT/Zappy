/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AWorld
*/

#pragma once
#include "IGraphical.hpp"
#include <SFML/Graphics.hpp>

namespace zappyGUI {
    class AGraphical: public IGraphical {
        public:
            AGraphical();
            ~AGraphical() = default;

            void setWindow(std::shared_ptr<zappyGUI::Window> window) final;
            void setGame(std::shared_ptr<zappyGUI::Game> game) final;
            virtual void display() override;
            virtual void update() override;
            virtual void handleEvents() override;

        protected:
            std::shared_ptr<zappyGUI::Window> _window;
            std::shared_ptr<zappyGUI::Game> _game;
    };
}
