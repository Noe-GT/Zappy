/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** AUIBlock
*/

#pragma once
#include "IUIBlock.hpp"

namespace UIBlocks {
    class AUIBlock: public IUIBlock {
        public:
            AUIBlock();
            ~AUIBlock() = default;
            void draw(std::shared_ptr<zappyGUI::Window> &window) override;
            void handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window) override;
            void setPosition(const std::pair<float, float> &position) override;
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;
            void setSize(const std::pair<float, float> &size) override;
            void setSize(const int size) override;
    
        protected:
            sf::Color _borderColor;
            sf::Color _backgroundColor;
            int _borderThickness;
            sf::Color _textColor;
            sf::Font _font;
        private:
    };
}

