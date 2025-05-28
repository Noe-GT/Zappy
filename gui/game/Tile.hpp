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

            std::vector <Player> getPlayers();
            Player getPlayer(int index);
            std::vector <std::shared_ptr <IRessource>> getRessource();

            void setPlayer(std::vector <Player> newVal);
            void setRessource(std::vector <std::shared_ptr <IRessource>> newVal);

            void addPlayer(Player newVal);
            void addRessource(std::shared_ptr <IRessource> newVal);

            void display();

        private:
            std::vector <Player> _player;
            std::vector <std::shared_ptr <IRessource>> _ressource;
    };
};
