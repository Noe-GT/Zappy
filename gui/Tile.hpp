/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.hpp
*/
#pragma once

#include "game/ressources/IRessource.hpp"
#include "game/Player.hpp"
#include "UI/shared/UIBlocks/PopupSelector/PopupSelector.hpp"
#include "game/ressources/Food.hpp"
#include "game/ressources/Linemate.hpp"
#include "game/ressources/Deraumere.hpp"
#include "game/ressources/Sibur.hpp"
#include "game/ressources/Mendiane.hpp"
#include "game/ressources/Phiras.hpp"
#include "game/ressources/Thystame.hpp"

namespace zappyGUI {
    class Player;

    class Tile {
        public:
            Tile(const std::pair<size_t, size_t> &pos);
            Tile(const zappyGUI::Tile &other);
            ~Tile() = default;

            std::vector <std::shared_ptr <Player>> &getPlayers();
            const std::vector <std::shared_ptr <Player>> &getPlayers() const;
            std::shared_ptr <Player> &getPlayer(int index);
            std::vector <std::pair<std::shared_ptr <IRessource>, int>> &getRessource();
            const std::pair<size_t, size_t> &getPos() const;

            void setPlayer(std::vector <std::shared_ptr <Player>> newVal);
            void setRessource( std::vector <std::pair<std::shared_ptr <IRessource>, int>> newVal);

            void addPlayer(std::shared_ptr <Player> newVal);
            void addRessource(std::shared_ptr <IRessource> newVal);

            zappyGUI::Tile& operator=(const Tile& other);

        private:
            std::pair<size_t, size_t> _pos;
            std::vector <std::shared_ptr <Player>> _players;
            std::vector <std::pair<std::shared_ptr <IRessource>, int>> _ressources;
    };
};
