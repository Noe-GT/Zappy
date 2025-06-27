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
        std::vector<std::shared_ptr<UIBlocks::IUIBlock>> getVisibleOptions() const;
        void scrollUp();
        void scrollDown();
        void setMaxVisibleOptions(int maxVisibleOptions);
        int getMaxVisibleOptions() const;
        void setOptions(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> options);
    private:
        int _maxVisibleOptions;
        size_t _currentOffset;
        std::vector<std::shared_ptr<UIBlocks::IUIBlock>> _options;
};

