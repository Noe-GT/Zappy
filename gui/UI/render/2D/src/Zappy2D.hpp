#pragma once
#include "../../../shared/AGraphical.hpp"
#define TILE_SIZE 50

namespace zappyGUI {
    class Zappy2D: public AGraphical {
        public:
            Zappy2D();
            ~Zappy2D() = default;
            void initialize(std::shared_ptr<zappyGUI::Window> window, std::shared_ptr<zappyGUI::Game> game) final;

        private:
            std::vector<std::vector<sf::RectangleShape>> _tiles;
    };
}
