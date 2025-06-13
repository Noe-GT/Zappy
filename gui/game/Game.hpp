/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/
#pragma once
#include "../Tile.hpp"

namespace zappyGUI {
    class IGraphical;
    class Game {
        public:
            Game();
            ~Game();

            int getFrequence();
            int getTeamNbr();
            bool isGameInProgess();
            std::vector <std::string> &getLogs();
            std::vector <std::vector <Tile>> &getMap();
            std::pair<size_t, size_t> getMapSize();
            std::vector <Player> &getPlayers();
            std::vector <std::pair<std::shared_ptr <Player>, int>> &getEggs();
            std::vector <std::string> &getTeams();

            void setFrequence(int newVal);
            void setTeamNbr(int newVal);
            void setIsGameInProgess(bool newVal);
            void setLogs(std::vector <std::string> newVal);
            void addLogs(std::string newVal);
            void setMap(std::vector <std::vector <Tile>> newVal);
            void setMapSize(int newX, int newY);
            void setPlayers(std::vector <Player> newVal);
            void addPlayer(Player newVal);
            void setEggs(std::vector <std::pair <std::shared_ptr <Player>, int>> newVal);
            void addEgg(std::shared_ptr <Player> newVal, int ID);
            void setTeams(std::vector <std::string> newVal);
            void addTeam(std::string newVal);

            void display(std::shared_ptr<zappyGUI::IGraphical> renderer) const;

        private:
            int _frequence;
            int _teamNbr;
            bool _gameInProgess;
            std::vector<Player> _players;
            std::vector<std::pair <std::shared_ptr <Player>, int>> _eggs;
            std::vector<std::string> _logs;
            std::pair<size_t, size_t> _mapSize;
            std::vector<std::vector <Tile>> _map;
            std::vector<std::string> _teams;
    };
};