/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.hpp
*/
#pragma once

#include "Ressources/IRessource.hpp"
#include "Player.hpp"

namespace zappyGUI {
    class Player;
    class Tile {
        public:
            Tile();
            ~Tile();

            std::vector <Player> getPlayers();
            Player getPlayer(int index);
            std::vector <IRessource> getRessource();

            void setPlayer(std::vector <Player> newVal);
            void setRessource(std::vector <IRessource> newVal);

            void addPlayer(Player newVal);
            void addRessource(IRessource newVal);

        private:
            std::vector <Player> _player;
            std::vector <IRessource> _ressource;
    };
};
