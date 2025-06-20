#pragma once
#include "../../../shared/AGraphical.hpp"
#include "Engine.hpp"
namespace zappyGUI {
    class Zappy3D: public AGraphical {
        public:
            Zappy3D();
            virtual ~Zappy3D() = default;

            void initialize(std::shared_ptr<zappyGUI::GUI> GUI) final;
            void handleEvents() final;
            void display() final;
            void update() final;
        private:
            std::shared_ptr<GUI> _gui;
            Engine _engine;
            Camera _camera;
            bool _fullscreen;
            bool _displayRessources;
            bool _mousePressed;
            sf::Vector2i _lastMousePos;
            glm::vec3 _mapCenter;
            int _selectedResourceType;

            bool shouldDisplayResource(int resourceType);
    };
}
