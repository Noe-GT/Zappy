/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/
#pragma once
#include "../Tile.hpp"
#include "../UI/shared/UIBlocks/List/List.hpp"
#include "../UI/shared/UIBlocks/Text/Text.hpp"
#include "../UI/shared/UIBlocks/Pair/Pair.hpp"
#include "../UI/shared/UIBlocks/Timer/Timer.hpp"
#include "../UI/shared/Window.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

namespace zappyGUI {
    class Player;
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
            const std::pair<unsigned int, unsigned int> &getMapSize() const;
            std::vector <Player> &getPlayers();
            std::vector <std::pair<std::shared_ptr <Player>, int>> &getEggs();
            std::vector <std::string> &getTeams();

            void setFrequence(int newVal);
            void setTeamNbr(int newVal);
            void setIsGameInProgess(bool newVal);
            void setLogs(std::vector <std::string> newVal);
            void addLogs(std::string newVal);
            void setMap(std::vector <std::vector <Tile>> newVal);
            void setMapSize(unsigned int newX, unsigned int newY);
            void setPlayers(std::vector <Player> newVal);
            void addPlayer(Player newVal);
            void setEggs(std::vector <std::pair <std::shared_ptr <Player>, int>> newVal);
            void addEgg(std::shared_ptr <Player> newVal, int ID);
            void setTeams(std::vector <std::string> newVal);
            void addTeam(std::string newVal);

            void display(std::shared_ptr<zappyGUI::IGraphical> renderer);
            void displayUI(std::shared_ptr<zappyGUI::Window> window);
            void handleUIEvents(const sf::Event& event, std::shared_ptr<zappyGUI::Window> window);
            void update();
            void updateSelectedTileSelector();

            void setSelectedTile(std::pair<float, float> windowPos, std::pair<int, int> mapPos);

            std::shared_ptr<zappyGUI::Player> getSelectedPlayer();

        private:
            int _frequence;
            int _teamNbr;
            bool _gameInProgess;
            std::vector<Player> _players;
            std::vector<std::pair <std::shared_ptr <Player>, int>> _eggs;
            std::vector<std::string> _logs;
            std::pair<unsigned int, unsigned int> _mapSize;
            std::vector<std::vector <Tile>> _map;
            std::vector<std::string> _teams;

            std::shared_ptr<Player> _selectedPlayer;
            std::shared_ptr<UIBlocks::PopupSelector> _playersListUI;
            std::shared_ptr<UIBlocks::Text> _selectedPlayerLevelText;
            std::shared_ptr<UIBlocks::PopupSelector> _spellsListUI;
            std::shared_ptr<UIBlocks::PopupSelector> _logsUI;
            std::map<std::string, std::pair<UIBlocks::Text, UIBlocks::Text>> _inventoryUI;
            std::shared_ptr<UIBlocks::Timer> _timerUI;
            std::shared_ptr<UIBlocks::Text> _playersListTitle;
            std::shared_ptr<UIBlocks::Text> _spellsListTitle;
            std::shared_ptr<UIBlocks::Text> _logsTitle;
            std::shared_ptr<UIBlocks::Pair> _selectedTileSelector;
            std::pair<int, int> _selectedTileMapPosition;
            std::pair<float, float> _selectedTileWindowPosition;



    };
};