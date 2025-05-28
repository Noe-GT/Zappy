/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Player.hpp
*/
#pragma once
#include "Spell/ISpell.hpp"
#include "Ressources/IRessource.hpp"
#include <memory>
#include <vector>
#include <string>
#include "Tile.hpp"
namespace zappyGUI {
    class Tile;
    class Player {
        public:
            Player();
            Player(Player&);
            ~Player();

            int getId();
            int getLvl();
            std::string getName();
            std::vector <IRessource> getInventory();
            std::shared_ptr <ISpell> getSpellInProgress();
            std::vector <Tile> getVisionData();
            std::vector <std::string> getLogs();

            void setId(int newVal);
            void setLvl(int newVal);
            void setName(std::string newVal);
            void setInventory(std::vector <IRessource> newVal);
            void setSpellInProgress(std::shared_ptr <ISpell> newval);
            void setVisionData(std::vector <Tile> newVal);
            void setLogs(std::vector <std::string> newVal);

        private:
            int _id;
            int _lvl;
            std::string _name;
            std::vector <IRessource> _inventory;
            std::shared_ptr <ISpell> _spellInProgress;
            std::vector <Tile> _visionData;
            std::vector <std::string> _logs;
    };
};