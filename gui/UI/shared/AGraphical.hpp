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

            virtual void initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize) override;
            virtual void display() override;
            virtual void displayTile(const zappyGUI::Tile &tile) = 0;
            virtual void updateTile(const zappyGUI::Tile &tile) = 0;
            virtual void update() override;
            virtual void handleEvents() override;
            virtual std::shared_ptr<zappyGUI::Window> getWindow() const override;

        protected:
            std::shared_ptr<zappyGUI::Window> _window;
    };
}
