/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scroller
*/

#pragma once
#include <vector>

class Scroller {
    public:
        Scroller(std::vector<std::string> &options, int maxVisibleOptions = 5);
        ~Scroller() = default;
        std::vector<std::string> getVisibleOptions() const;
        void scrollUp();
        void scrollDown();
        void setMaxVisibleOptions(int maxVisibleOptions);
        int getMaxVisibleOptions() const;
    private:
        int _maxVisibleOptions;
        int _currentOffset;
        std::vector<std::string> _options;
};

