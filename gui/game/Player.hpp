/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Player.hpp
*/
#pragma once
#include "spell/ISpell.hpp"
#include "ressources/IRessource.hpp"
#include <memory>
#include <vector>
#include <string>
#include "Tile.hpp"

namespace zappyGUI {
    class Tile;
    enum orientation {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
    class Player {
        public:
            Player();
            Player(const Player&);
            ~Player();

            int getId();
            int getLvl();
            std::string getName();
            std::vector <std::pair <std::shared_ptr <IRessource>, int>> &getInventory();
            std::shared_ptr <ISpell> &getSpellInProgress();
            std::vector <Tile> &getVisionData();
            std::vector <std::string> &getLogs();
            std::pair <int, int> getPos();
            orientation getOrientation();
            bool isLastSpellSucess();

            void setId(int newVal);
            void setLvl(int newVal);
            void setName(std::string newVal);
            void setInventory(std::vector <std::pair <std::shared_ptr <IRessource>, int>> newVal);
            void setSpellInProgress(std::shared_ptr <ISpell> newval);
            void setVisionData(std::vector <Tile> newVal);
            void setLogs(std::vector <std::string> newVal);
            void setPos(std::pair <int, int> newVal);
            void setOrientation(int newVal);
            void setLastSpellSucess(bool newVal);

        private:
            int _id;
            int _lvl;
            bool _lastspellSucess;
            std::pair <int, int> _pos;
            std::string _name;
            orientation _orientation;
            std::vector <std::pair <std::shared_ptr <IRessource>, int>> _inventory;
            std::shared_ptr <ISpell> _spellInProgress;
            std::vector <Tile> _visionData;
            std::vector <std::string> _logs;
    };
};