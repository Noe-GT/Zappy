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
            PopupSelector(std::vector<std::shared_ptr<IUIBlock>> &options, std::pair<int, int> position, std::pair<int, int> size);
            ~PopupSelector() = default;

            void draw(zappyGUI::Window &window) override;
            void handleEvent(const sf::Event &event) override;
            void setPosition(const std::pair<int, int> &position) override;

            bool isInside(int x, int y) const;
            const std::shared_ptr<IUIBlock> &getSelected() const;
            void open();
            void close();

        private:
            std::pair<int, int> _position;
            std::pair<int, int> _size;
            Scroller _options;
            sf::RectangleShape _background;
            std::shared_ptr<IUIBlock> _selected;
            bool _isOpen;
    };
}
