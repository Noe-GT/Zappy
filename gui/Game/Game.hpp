/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/
#pragma once
#include "Tile.hpp"

namespace zappyGUI {
    class Game {
        public:
            Game();
            ~Game();

            int getFrequence();
            int getTeamNbr();
            bool isGameInProgess();
            std::vector <std::string> getLogs();
            std::vector <std::vector <Tile>> getMap();

            void setFrequence(int newVal);
            void setTeamNbr(int newVal);
            void isGameInProgess(bool newVal);
            void setLogs(std::vector <std::string> newVal);
            void addLogs(std::string newVal);
            void setMap(std::vector <std::vector <Tile>> newVal);

            void display();

        private:
            int _frequence;
            int _teamNbr;
            bool _gameInProgess;
            std::vector <std::string> _logs;
            std::vector <std::vector <Tile>> _map;
    };
};