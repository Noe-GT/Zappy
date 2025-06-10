/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** Window.hpp*
*/
#pragma once
#include <SFML/Graphics.hpp>

namespace zappyGUI {
    class Window {
    public:
        Window();
        ~Window();
        Window(const Window &other);
        Window& operator=(const Window &other);

        void switchFullscreen();
        bool pollEvent();
        void display();
        void clear();
        void close();
        bool isOpen();
        const std::pair<size_t, size_t> &getSize() const;

        sf::RenderWindow& getRenderWindow();
        sf::Event &getEvent();

    private:
        sf::Event _event;
        sf::RenderWindow _window;
        bool _isFullscreen;
    };
}
