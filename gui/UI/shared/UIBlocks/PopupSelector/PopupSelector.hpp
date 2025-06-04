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
            PopupSelector(std::vector<std::shared_ptr<IUIBlock>> &options, std::pair<float, float> position, std::pair<float, float> size);
            ~PopupSelector() = default;

            void draw(zappyGUI::Window &window) override;
            void handleEvent(const sf::Event &event) override;
            void setPosition(const std::pair<float, float> &position) override;
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;

            bool isInside(int x, int y) const;
            const std::shared_ptr<IUIBlock> &getSelected() const;
            void open();
            void close();

        private:
            std::pair<float, float> _position;
            std::pair<float, float> _size;
            Scroller _options;
            sf::RectangleShape _background;
            std::shared_ptr<IUIBlock> _selected;
            bool _isOpen;
    };
}
