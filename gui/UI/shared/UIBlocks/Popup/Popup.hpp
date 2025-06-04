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
            Popup(std::string &content, std::pair<float, float> position, std::pair<float, float> size);
            ~Popup() = default;
            void draw(zappyGUI::Window &window) override;
            void setPosition(const std::pair<float, float> &position) override;
            void handleEvent(const sf::Event &event) override;
            void open();
            void close();
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;

        private:
            bool _isOpen;
            std::pair<float, float> _position;
            std::pair<float, float> _size;
            Text _content;
            sf::RectangleShape _background;
            std::pair<std::shared_ptr<IUIBlock>, std::shared_ptr<IUIBlock>> _pair;
    };
}
