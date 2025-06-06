/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AGraphical
*/

#pragma once
#include "IGraphical.hpp"

namespace zappyGUI {
    class AGraphical: public IGraphical {
        public:
            virtual ~AGraphical() override;
            virtual void display() override;
            virtual void update() override;
            virtual void handleEvents() override;
        private:
    };
}
