/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.hpp
*/
#pragma once

#include "ressources/IRessource.hpp"
#include "Player.hpp"
#include "../UI/shared/UIBlocks/PopupSelector/PopupSelector.hpp"

namespace zappyGUI {
    class Player;
    class Tile {
        public:
            Tile();
            ~Tile();

            std::vector <std::shared_ptr <Player>> &getPlayers();
            std::shared_ptr <Player> &getPlayer(int index);
            std::vector <std::pair<std::shared_ptr <IRessource>, int>> &getRessource();

            void setPlayer(std::vector <std::shared_ptr <Player>> newVal);
            void setRessource( std::vector <std::pair<std::shared_ptr <IRessource>, int>> newVal);

            void addPlayer(std::shared_ptr <Player> newVal);
            void addRessource(std::shared_ptr <IRessource> newVal);
            void display();

        private:
            std::vector <std::shared_ptr <Player>> _players;
            std::vector <std::pair<std::shared_ptr <IRessource>, int>> _ressources;
    };
};
