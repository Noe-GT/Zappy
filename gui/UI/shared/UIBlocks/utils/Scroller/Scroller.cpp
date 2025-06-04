/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scroller
*/

#include "Scroller.hpp"

Scroller::Scroller(std::vector<std::shared_ptr<UIBlocks::IUIBlock>> &options, int maxVisibleOptions): 
    _maxVisibleOptions(maxVisibleOptions),
    _currentOffset(0),
    _options(options)
{
}

std::vector<std::shared_ptr<UIBlocks::IUIBlock>> Scroller::getVisibleOptions() const
{
    std::vector<std::shared_ptr<UIBlocks::IUIBlock>> visibleOptions;
    size_t start = this->_currentOffset;
    
    for (size_t i = start; i < start + _maxVisibleOptions or i < this->_options.size(); ++i)
        visibleOptions.push_back(this->_options[i]);
    return visibleOptions;
}

void Scroller::scrollUp()
{
    if (this->_currentOffset > 0)
        this->_currentOffset--;
}

void Scroller::scrollDown()
{
    if (this->_currentOffset < this->_options.size() - this->_maxVisibleOptions)
        this->_currentOffset++;
}

void Scroller::setMaxVisibleOptions(int maxVisibleOptions)
{
    this->_maxVisibleOptions = maxVisibleOptions;
    this->_currentOffset = 0;
}

int Scroller::getMaxVisibleOptions() const
{
    return _maxVisibleOptions;
}