/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scroller
*/

#pragma once
#include <vector>
#include <string>

#include "../../IUIBlock.hpp"

class Scroller {
    public:
        Scroller(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> &options, int maxVisibleOptions = 5);
        ~Scroller() = default;
        std::vector<std::shared_ptr<UIBlocks::IUIBlock>> &getVisibleOptions() const;
        void scrollUp();
        void scrollDown();
        void setMaxVisibleOptions(int maxVisibleOptions);
        int getMaxVisibleOptions() const;
    private:
        int _maxVisibleOptions;
        int _currentOffset;
        std::vector<std::shared_ptr<UIBlocks::IUIBlock>> _options;
};

