/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Text
*/

#pragma once

#include "../AUIBlock.hpp"

namespace UIBlocks {
    class Text: public AUIBlock {
        public:
            Text(std::string text, std::pair<float, float> position, int size);
            Text(std::string text, std::pair<float, float> position, int size, std::string font);
            ~Text() = default;
            void draw(zappyGUI::Window &window) override;
            void handleEvent(const sf::Event &event, zappyGUI::Window &window) override;
            void setPosition(const std::pair<float, float> &position) override;
            void setText(const std::string &text);
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;
            void setSize(const std::pair<float, float> &size) override;
            void setSize(const int size) override;


        private:
            std::pair<float, float> _position;
            sf::Text _text;
            sf::RectangleShape _background;
    };
}
