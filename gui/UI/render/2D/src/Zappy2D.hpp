#pragma once
#include <SFML/Graphics.hpp>
#include "../../../shared/Window.hpp"
#include "../../../shared/AGraphical.hpp"
#include "../../../../game/Game.hpp"
namespace zappyGUI {
    class Zappy2D: public AGraphical {
    public:
        Zappy2D();
        virtual ~Zappy2D() = default;

    private:
        Player _player;
    };
}
