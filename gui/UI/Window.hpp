/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Window.hpp
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ZappyGui {
    class window {
        public:
            window();
            ~window();

            void switchFullscreen();
            bool pollEvent(sf::Event &event);
            void display();
            sf::Event &getEvent();
            bool isOpen();
        private:
            bool _isFullscreen;
            sf::RenderWindow _window;
            sf::Event _event;
    };
}