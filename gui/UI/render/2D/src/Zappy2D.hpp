#pragma once
#include "../../../shared/AGraphical.hpp"
// #define BASE_TILE_SIZE 32
// #define BASE_PLAYER_SIZE 10
// #define BASE_RESSOURCE_SIZE 16
// #define ZOOM_COEFF_MAX (float)5.0
// // #define ZOOM_COEFF_MIN (float)0.1
// #define ZOOM_COEFF_SENSITIVITY (float)0.1
// #define MAP_OFFSET_SENSITIVITY (float)10.0
#define ASSETS_FOLDER "gui/UI/render/2D/assets/"

namespace zappyGUI {
    constexpr float ZOOM_COEFF_MIN = 0.1f;
    constexpr float BASE_TILE_SIZE = 32.0f;
    constexpr float BASE_PLAYER_SIZE = 10.0f;
    constexpr float BASE_RESSOURCE_SIZE = 16.0f;
    constexpr float ZOOM_COEFF_MAX = 5.0f;
    constexpr float ZOOM_COEFF_SENSITIVITY = 0.1f;
    constexpr float MAP_OFFSET_SENSITIVITY = 10.0f;

    class Zappy2D: public AGraphical {
        public:
            enum ressourceType {
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME
            };

            class AssetPool {
                public:
                    AssetPool();
                    ~AssetPool() = default;

                    sf::Texture _tileTexture;
                    sf::Texture _playerTexture;
                    sf::Texture _linemateTexture;
                    sf::Texture _deraumereTexture;
                    sf::Texture _siburTexture;
                    sf::Texture _mendianeTexture;
                    sf::Texture _phirasTexture;
                    sf::Texture _thystameTexture;
                    sf::Texture _foodTexture;
            };

            class RTile {
                public:
                    RTile(int x, int y, std::shared_ptr<float> zoomCoeff, std::shared_ptr<std::pair<float, float>> mapOffset,
                        std::shared_ptr<zappyGUI::Zappy2D::AssetPool> assets, std::shared_ptr<zappyGUI::Zappy2D::ressourceType> displayRessourceType);
                    ~RTile() = default;

                    void display(std::shared_ptr<zappyGUI::Window> window) const;
                    void update(const zappyGUI::Tile &tile);

                private:
                    void handleRessouces(const zappyGUI::Tile &tile);
                    void setRessource();
                    void setRessourceTexture();
                    void updatePlayers(const zappyGUI::Tile &tile);

                    std::shared_ptr<float> _zoomCoeff;
                    std::shared_ptr<std::pair<float, float>> _mapOffset;
                    std::shared_ptr<zappyGUI::Zappy2D::ressourceType> _displayRessourceType;
                    std::shared_ptr<zappyGUI::Zappy2D::AssetPool> _assets;
                    sf::Sprite _back;
                    sf::Sprite _ressource;
            };

            Zappy2D();
            ~Zappy2D() = default;
            void initialize(std::shared_ptr<zappyGUI::GUI> gui) final;
            void displayTile(const zappyGUI::Tile &tile) final;
            void updateTile(const zappyGUI::Tile &tile) final;
            void display() final;
            void update() final;
            void handleEvents() final;

        private:
            void updateZoom(bool zoomOut);
            void updatePosition(sf::Keyboard::Key eventCode);
            void computeZoom(std::pair<size_t, size_t> mapSize);

            std::shared_ptr<zappyGUI::Zappy2D::AssetPool> _assets;
            std::vector<std::vector<zappyGUI::Zappy2D::RTile>> _tiles;
            std::shared_ptr<float> _zoomCoeff;
            std::shared_ptr<std::pair<float, float>> _mapOffset;
            std::shared_ptr<zappyGUI::Zappy2D::ressourceType> _displayRessourceType;
    };
}
