/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Text
*/

#pragma once

#include "../IUIBlock.hpp"

namespace UIBlocks {
    class Text: public IUIBlock {
        public:
            Text(std::string text, std::pair<float, float> position, int size);
            ~Text() = default;
            void draw(zappyGUI::Window &window) override;
            void handleEvent(const sf::Event &event) override;
            void setPosition(const std::pair<float, float> &position) override;
            void setText(const std::string &text);
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;


        private:
            std::pair<float, float> _position;
            std::pair<float, float> _size;
            sf::Text _text;
            sf::Font _font;
            sf::RectangleShape _background;
    };
}
