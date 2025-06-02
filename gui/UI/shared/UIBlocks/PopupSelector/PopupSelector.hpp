/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PopupSelector
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/Scroller/Scroller.hpp"
#include "../IUIBlock.hpp"

namespace UIBlocks {
    class PopupSelector: public IUIBlock {
        public:
            PopupSelector(std::vector<std::string> &options);
            ~PopupSelector() = default;

            void draw(zappyGUI::Window &window) override;
            bool isInside(int x, int y) const;
            void handleEvent(const sf::Event &event) override;
            const std::string &getSelected() const;
            void open();
            void close();
    
        protected:
        private:
            std::pair<int, int> _position;
            std::pair<int, int> _size;
            Scroller _options;
            sf::RectangleShape _background;
            std::string _selected;
            bool _isOpen;
    };
}

