/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Image
*/

#pragma once

#include "../AUIBlock.hpp"
#include "../Popup/Popup.hpp"
#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>


namespace UIBlocks {
    class Image: public AUIBlock {
        public:
            Image(const std::string &path, std::pair<float, float> position, std::pair<float, float> size, std::string &alternativeText);
            ~Image() = default;
            void draw(std::shared_ptr<zappyGUI::Window> &window) override;
            void setPosition(const std::pair<float, float> &position) override;
            void handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window) override;
            bool isInside(int x, int y) const;
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;
            void setSize(const std::pair<float, float> &size) override;
            void setSize(const int size) override;

        private:
            std::pair<float, float> _position;
            std::pair<float, float> _size;
            Popup _alternativeText;
            sf::Sprite _sprite;
            sf::Texture _texture;
            sf::Image _image;
    };
}
