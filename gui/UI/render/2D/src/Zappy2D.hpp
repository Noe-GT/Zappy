#pragma once
#include "../../../shared/AGraphical.hpp"
#define TILE_SIZE 40

namespace zappyGUI {
    class Zappy2D: public AGraphical {
        public:
            class RTile {
                public:
                    RTile(int x, int y);
                    ~RTile() = default;

                    void display(std::shared_ptr<zappyGUI::Window> window) const;
                    void update(const zappyGUI::Tile &tile);

                private:
                    sf::RectangleShape _back;
                    std::vector<sf::CircleShape> _players;
            };

            Zappy2D();
            ~Zappy2D() = default;
            void initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize) final;
            void displayTile(const zappyGUI::Tile &tile) final;
            void display() final;
            void update() final;

        private:
            std::vector<std::vector<zappyGUI::Zappy2D::RTile>> _tiles;
    };
}
