/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Timer
*/

#pragma once

#include "../IUIBlock.hpp"
#include "../Text/Text.hpp"

namespace UIBlocks {
    class Timer: public IUIBlock {
        public:
            Timer(std::pair<float, float> position, int size);
            ~Timer() = default;
            void draw(zappyGUI::Window &window) override;
            void handleEvent(const sf::Event &event) override;
            void setPosition(const std::pair<float, float> &position) override;
            void start();
            void restart();
            const std::variant<std::string, std::vector<std::shared_ptr<IUIBlock>>> getValue() const override;


        private:
            sf::Clock _timer;
            Text _text;
    };
}
