/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Popup
*/

#pragma once

#include "../IUIBlock.hpp"
#include "../Text/Text.hpp"
#include <memory>

namespace UIBlocks {
    class Popup: public IUIBlock {
        public:
            Popup(std::string &content, const std::string font, std::pair<int, int> position, std::pair<int, int> size);
            ~Popup() = default;
            void draw(zappyGUI::Window &window) override;
            void setPosition(const std::pair<int, int> &position) override;
            void handleEvent(const sf::Event &event) override;
            void open();
            void close();
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;

        private:
            bool _isOpen;
            std::pair<int, int> _position;
            std::pair<int, int> _size;
            Text _content;
            sf::RectangleShape _background;
            std::pair<std::shared_ptr<IUIBlock>, std::shared_ptr<IUIBlock>> _pair;
    };
}
