/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Image
*/

#pragma once

#include "../IUIBlock.hpp"
#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>

namespace UIBlocks {
    class Image: public IUIBlock {
        public:
            Image(const std::string &path, std::pair<int, int> position, std::pair<int, int> size, std::string &alternativeText);
            ~Image() = default;
            void draw(zappyGUI::Window &window) override;
            void setPosition(const std::pair<int, int> &position) override;
            void handleEvent(const sf::Event &event) override;
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;

        private:
            std::string _alternativeText;
            sf::Sprite _sprite;
            sf::Texture _texture;
            sf::Image _image;
    };
}
