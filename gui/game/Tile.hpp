/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.hpp
*/
#pragma once

#include "ressources/IRessource.hpp"
#include "Player.hpp"

namespace zappyGUI {
    class Player;
    class Tile {
        public:
            Tile();
            ~Tile();

            std::vector <std::shared_ptr <Player>> getPlayers();
            std::shared_ptr <Player> getPlayer(int index);
            std::vector <std::shared_ptr <IRessource>> getRessource();

            void setPlayer(std::vector <std::shared_ptr <Player>> newVal);
            void setRessource(std::vector <std::shared_ptr <IRessource>> newVal);

            void addPlayer(std::shared_ptr <Player> newVal);
            void addRessource(std::shared_ptr <IRessource> newVal);
            void display();

        private:
            std::vector <std::shared_ptr <Player>> _player;
            std::vector <std::shared_ptr <IRessource>> _ressource;
    };
};
