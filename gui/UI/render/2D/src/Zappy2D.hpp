#pragma once
#include "../../../shared/AGraphical.hpp"
#define BASE_TILE_SIZE 70
#define BASE_PLAYER_SIZE 10
#define ZOOM_COEFF_MAX 5
#define ZOOM_COEFF_MIN 0.5
#define ZOOM_COEFF_SENSITIVITY 0.3

namespace zappyGUI {
    class Zappy2D: public AGraphical {
        public:
            class RTile {
                public:
                    RTile(int x, int y, std::shared_ptr<double> zoomCoeff);
                    ~RTile() = default;

                    void display(std::shared_ptr<zappyGUI::Window> window) const;
                    void update(const zappyGUI::Tile &tile);

                private:
                    std::shared_ptr<double> _zoomCoeff;
                    sf::RectangleShape _back;
                    std::vector<sf::CircleShape> _players;
            };

            Zappy2D();
            ~Zappy2D() = default;
            void initialize(std::shared_ptr<zappyGUI::Window> window, std::pair<size_t, size_t> mapSize) final;
            void displayTile(const zappyGUI::Tile &tile) final;
            void updateTile(const zappyGUI::Tile &tile) final;
            void display() final;
            void update() final;
            void handleEvents() final;

        private:
            void updateZoom(bool zoomOut);

            std::vector<std::vector<zappyGUI::Zappy2D::RTile>> _tiles;
            std::shared_ptr<double> _zoomCoeff;
    };
}
