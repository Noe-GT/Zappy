/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Window.hpp
*/
#include <SFML/Graphics.hpp>

namespace zappyGUI {
    class Window {
        public:
            Window();
            ~Window();
            Window(Window &window);

            void switchFullscreen();
            bool pollEvent(sf::Event &event);
            void display();
            sf::Event &getEvent();
            bool isOpen();
            sf::RenderWindow &getRenderWindow();
        private:
            bool _isFullscreen;
            sf::RenderWindow _window;
            sf::Event _event;
    };
}