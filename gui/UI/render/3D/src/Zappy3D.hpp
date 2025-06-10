#pragma once
#include "../../../shared/AGraphical.hpp"

namespace zappyGUI {
    class Zappy3D: public AGraphical {
        public:
            Zappy3D();
            virtual ~Zappy3D() = default;

            void displayTile(const zappyGUI::Tile &tile) final;
            void updateTile(const zappyGUI::Tile &tile) final;
        private:
    };
}
