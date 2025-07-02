#pragma once
#include "../../../shared/AGraphical.hpp"
#include "../../../../game/Game.hpp"
#define ASSETS_FOLDER "gui/UI/render/2D/assets/"
#define GLOBAL_ASSETS_FOLDER "../../../../../assets/"

namespace zappyGUI {
    constexpr float ZOOM_COEFF_MIN = 0.1f;
    constexpr float BASE_TILE_SIZE = 32.0f;
    constexpr float BASE_PLAYER_SIZE = 10.0f;
    constexpr float BASE_RESSOURCE_SIZE = 16.0f;
    constexpr float RESSOURCE_AMMOUNT_OFFSET = 20.0f;
    constexpr int RESSOURCE_FONT_SIZE = 60;
    constexpr float ZOOM_COEFF_MAX = 5.0f;
    constexpr float ZOOM_COEFF_SENSITIVITY = 0.1f;
    constexpr int MAP_OFFSET_SENSITIVITY = 10;

    class Zappy2D: public AGraphical{
        public:
            enum ressourceType {
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME,
                ALL
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
                    sf::Font _font;
            };

            class RTile {
                public:
                    RTile(int x, int y, zappyGUI::Zappy2D &ui);
                    ~RTile() = default;

                    void display(std::shared_ptr<zappyGUI::Window> window) const;
                    void update(const zappyGUI::Tile &tile, zappyGUI::Zappy2D &ui);

                private:
                    void handleRessouces(const zappyGUI::Tile &tile, zappyGUI::Zappy2D &ui);
                    void setRessource(zappyGUI::Zappy2D::ressourceType ressourceType, int amount, zappyGUI::Zappy2D &ui);
                    void setRessourceTexture(zappyGUI::Zappy2D::ressourceType ressourceType, zappyGUI::Zappy2D &ui);
                    void updatePlayers(const zappyGUI::Tile &tile, zappyGUI::Zappy2D &ui);
                    void updatePlayer(const zappyGUI::Tile &tile, const  std::shared_ptr<zappyGUI::Player> &player, zappyGUI::Zappy2D &ui);

                    sf::Sprite _back;
                    sf::Sprite _ressource;
                    sf::Text _ressourceAmount;
            };

            Zappy2D();
            virtual ~Zappy2D() = default;
            void initialize(std::shared_ptr<zappyGUI::GUI> gui) final;
            void displayTile(const zappyGUI::Tile &tile) final;
            void updateTile(const zappyGUI::Tile &tile) final;
            void display() final;
            void update() final;
            void handleEvents() final;

            const std::string &getDisplayTeam() const;
            const float &getZoomCoeff() const;
            const std::pair<int, int> &getMapOffset() const;
            const zappyGUI::Zappy2D::ressourceType &getDisplayRessourceType() const;
            const zappyGUI::Zappy2D::AssetPool &getAssets() const;

        private:
            void updateZoom(bool zoomOut);
            void updatePosition(sf::Keyboard::Key eventCode);
            void zoomFill();
            void centerMap();
            void handleEventKey();
            void handleEventMouse();

            zappyGUI::Zappy2D::AssetPool _assets;
            std::vector<std::vector<zappyGUI::Zappy2D::RTile>> _tiles;
            float _zoomCoeff;
            std::pair<int, int> _mapOffset;
            zappyGUI::Zappy2D::ressourceType _displayRessourceType;
            std::string _displayTeam;
    };
}
