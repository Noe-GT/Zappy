/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Spell.hpp
*/
#pragma once

#include <ctime>
#include <memory>
#include <vector>

namespace zappyGUI {

    class Player;
    class Spell {
        public:
            Spell();
            ~Spell();

            int getLevel();
            std::time_t getStartTime();
            std::shared_ptr<Player> getCaster();
            std::pair <int, int> getPos();
            double getSpendedTime();
            std::vector<std::shared_ptr<Player>> &getParticipant();

            void setLevel(int newVal);
            void setStartTime(std::time_t newVal);
            void resetStartTime();
            void setCaster(std::shared_ptr<Player> newVal);
            void setPos(int newX, int newY);
            void setParticipant(std::vector<std::shared_ptr<Player>> newVal);

        private:
            int _lvl;
            std::time_t _startTime;
            std::shared_ptr<Player> _caster;
            std::vector<std::shared_ptr<Player>> _participant;
            std::pair <int, int> _pos;
    };
}