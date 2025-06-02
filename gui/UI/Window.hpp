/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** Window.hpp*
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace zappyGUI {
    class window {
    public:
        window();
        ~window();
        window(const window &other);
        window& operator=(const window &other);

        void switchFullscreen();
        bool pollEvent();
        void display();
        void clear();
        void close();
        bool isOpen();

        sf::RenderWindow& getRenderWindow();
        sf::Event &getEvent();

    private:
        sf::Event _event;
        sf::RenderWindow _window;
        bool _isFullscreen;
    };
}
