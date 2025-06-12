#pragma once
#include "../../../shared/AGraphical.hpp"
#define BASE_TILE_SIZE 32
#define BASE_PLAYER_SIZE 10
#define ZOOM_COEFF_MAX 5
#define ZOOM_COEFF_MIN 0.1
#define ZOOM_COEFF_SENSITIVITY 0.1
#define ASSETS_FOLDER "gui/UI/render/2D/assets/"

namespace zappyGUI {
    class Zappy2D: public AGraphical {
        public:
            class AssetPool {
                public:
                    AssetPool();
                    ~AssetPool() = default;

                    sf::Texture _tileTexture;
                    sf::Texture _linemateTexture;
                    sf::Texture _deraumereTexture;
                    sf::Texture _siburTexture;
                    sf::Texture _mendianeTexture;
                    sf::Texture _phirasTexture;
                    sf::Texture _thystameTexture;
            };

            class RTile {
                public:
                    RTile(int x, int y, std::shared_ptr<double> zoomCoeff, std::shared_ptr<std::pair<double, double>> mapOffset, std::shared_ptr<zappyGUI::Zappy2D::AssetPool> assets);
                    ~RTile() = default;

                    void display(std::shared_ptr<zappyGUI::Window> window) const;
                    void update(const zappyGUI::Tile &tile);

                private:
                    std::shared_ptr<double> _zoomCoeff;
                    std::shared_ptr<std::pair<double, double>> _mapOffset;
                    // sf::RectangleShape _back;
                    std::shared_ptr<zappyGUI::Zappy2D::AssetPool> _assets;


                    sf::Sprite _back;
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

            std::shared_ptr<zappyGUI::Zappy2D::AssetPool> _assets;
            std::vector<std::vector<zappyGUI::Zappy2D::RTile>> _tiles;
            std::shared_ptr<double> _zoomCoeff;
            std::shared_ptr<std::pair<double, double>> _mapOffset;
    };
}
