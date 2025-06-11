#pragma once
#include "../../../shared/AGraphical.hpp"

namespace zappyGUI {
    class Zappy3D: public AGraphical {
        public:
            Zappy3D();
            virtual ~Zappy3D() = default;

            void display() final;
            void update() final;
        private:
    };
}
