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

            virtual void initialize(std::shared_ptr<zappyGUI::GUI> gui) override;
            virtual void display() override;
            virtual void displayTile(const zappyGUI::Tile &tile) override = 0;
            virtual void updateTile(const zappyGUI::Tile &tile) override = 0;
            virtual void update() override;
            virtual void handleEvents(Game &game) override;
            virtual std::shared_ptr<zappyGUI::Window> getWindow() const override;

        protected:
            std::shared_ptr<zappyGUI::Window> _window;
            std::shared_ptr<zappyGUI::GUI> _gui;
    };
}
