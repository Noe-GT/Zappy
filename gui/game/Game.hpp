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
            std::vector <std::string> &getLogs();
            std::vector <std::vector <Tile>> &getMap();
            std::pair<int, int> getMapSize();
            std::vector <Player> &getPlayers();
            Player getPlayer(int id);

            void setFrequence(int newVal);
            void setTeamNbr(int newVal);
            void setIsGameInProgess(bool newVal);
            void setLogs(std::vector <std::string> newVal);
            void addLogs(std::string newVal);
            void setMap(std::vector <std::vector <Tile>> newVal);
            void setMapSize(int newX, int newY);
            void setPlayers(std::vector <Player> newVal);
            void addPlayer(Player newVal);

            void display();

        private:
            int _frequence;
            int _teamNbr;
            bool _gameInProgess;
            std::vector <Player> _players;
            std::vector <std::string> _logs;
            std::pair <int, int> _mapSize;
            std::vector <std::vector <Tile>> _map;
    };
};