#pragma once
#include "../../../shared/AGraphical.hpp"
#define BASE_TILE_SIZE 70
#define BASE_PLAYER_SIZE 10
#define ZOOM_COEFF_MAX 5.0
#define ZOOM_COEFF_MIN 0.5
#define ZOOM_COEFF_SENSITIVITY 0.3
#define MARGIN 200

namespace zappyGUI {
    class Zappy2D: public AGraphical {
        public:
            class RTile {
                public:
                    RTile(int x, int y, double zoomCoeff);
                    ~RTile() = default;

                    void display(std::shared_ptr<zappyGUI::Window> window, float offsetX, float offsetY) const;
                    void update(const zappyGUI::Tile &tile);
                    void updateZoom(double newZoom);

                private:
                    void updateVisuals(int x, int y);

                    double _zoomCoeff;
                    sf::RectangleShape _back;
                    std::vector<sf::CircleShape> _players;
                };

                Zappy2D();
                ~Zappy2D() = default;

                void initialize(std::shared_ptr<zappyGUI::GUI> GUI) final;
                void display() final;
                void update() final;
                void handleEvents() final;

                std::vector<std::vector<RTile>> &getTiles();
                RTile &getTile(int x, int y);

            private:
                void updateTile(const zappyGUI::Tile &tile);
                void updateZoom(bool zoomOut);
                void computeZoom();

                std::vector<std::vector<RTile>> _tiles;
                double _zoomCoeff;
                std::shared_ptr <GUI> _GUI;
    };
}
