#pragma once
#include "../../../shared/AGraphical.hpp"

namespace zappyGUI {
    class Zappy2D: public AGraphical {
    public:
        Zappy2D();
        ~Zappy2D() = default;
    private:
    };
}

// namespace zappyGUI {
//     class Zappy2D: public zappyGUI::AGraphical {
//         public:
//             Zappy2D(zappyGUI::Window &window, zappyGUI::Game &game);
//             ~Zappy2D() = default;

//             void display() final;
//             void update() final;
//             void handleEvents() final;

//         private:
//             std::vector<std::vector<sf::RectangleShape>> _tiles;
//     };
// }

