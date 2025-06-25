/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** PopupSelector
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/Scroller/Scroller.hpp"
#include "../AUIBlock.hpp"

namespace UIBlocks {
    class PopupSelector: public AUIBlock {
        public:
            PopupSelector(std::vector<std::shared_ptr<IUIBlock>> &options, std::pair<float, float> position);
            PopupSelector(std::vector<std::shared_ptr<IUIBlock>> &options, std::pair<float, float> position, std::pair<float, float> size);
            ~PopupSelector() = default;

            void draw(std::shared_ptr<zappyGUI::Window> &window) override;
            void handleEvent(const sf::Event &event, std::shared_ptr<zappyGUI::Window> &window) override;
            void setPosition(const std::pair<float, float> &position) override;
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;
            void setOptions(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> options);


            bool isInside(int x, int y) const;
            const std::shared_ptr<IUIBlock> &getSelected() const;
            void open();
            void close();

            void setSize(const std::pair<float, float> &size) override;
            void setSize(const int size) override;
            void updateMaxVisibleOptions();

        private:
            std::pair<float, float> _position;
            std::pair<float, float> _size;
            Scroller _options;
            sf::RectangleShape _background;
            std::shared_ptr<IUIBlock> _selected;
            bool _isOpen;
    };
}
