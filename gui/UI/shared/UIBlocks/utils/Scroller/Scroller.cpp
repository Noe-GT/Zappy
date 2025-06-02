/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Scroller
*/

#include "Scroller.hpp"

Scroller::Scroller(std::vector<std::string> &options, int maxVisibleOptions): 
    _maxVisibleOptions(maxVisibleOptions),
    _currentOffset(0),
    _options(options)
{
}

std::vector<std::string> Scroller::getVisibleOptions() const
{
    std::vector<std::string> visibleOptions;
    int start = _currentOffset;
    
    for (int i = start; i < start + _maxVisibleOptions or i < this->_options.size(); ++i)
        visibleOptions.push_back(this->_options[i]);
    return visibleOptions;
}

void Scroller::scrollUp()
{
    if (_currentOffset > 0)
        _currentOffset--;
}

void Scroller::scrollDown()
{
    if (_currentOffset < _options.size() - _maxVisibleOptions)
        _currentOffset++;
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