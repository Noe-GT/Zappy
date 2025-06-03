/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.hpp
*/

#pragma once
#include "UI/shared/Window.hpp"
#include "client/Client.hpp"
#include "game/Game.hpp"
#include "client/commands/Icommand.hpp"
#include "client/commands/game/Seg.hpp"
#include "client/commands/game/Smg.hpp"
#include "client/commands/game/Tna.hpp"
#include "client/commands/map/Bct.hpp"
#include "client/commands/map/Mct.hpp"
#include "client/commands/map/Msz.hpp"
#include "client/commands/misc/Sbp.hpp"
#include "client/commands/misc/Suc.hpp"
#include "client/commands/player/egg/Ebo.hpp"
#include "client/commands/player/egg/Edi.hpp"
#include "client/commands/player/egg/Enw.hpp"
#include "client/commands/player/egg/Pfk.hpp"
#include "client/commands/player/player/Pbc.hpp"
#include "client/commands/player/player/Pdi.hpp"
#include "client/commands/player/player/Pex.hpp"
#include "client/commands/player/player/Pic.hpp"
#include "client/commands/player/player/Pie.hpp"
#include "client/commands/player/player/Pin.hpp"
#include "client/commands/player/player/Plv.hpp"
#include "client/commands/player/player/Pnw.hpp"
#include "client/commands/player/player/Ppo.hpp"
#include "client/commands/ressources/Pdr.hpp"
#include "client/commands/ressources/Pgt.hpp"
#include "client/commands/settings/Sgt.hpp"
#include "client/commands/settings/Sst.hpp"
#include <memory>
#include <unordered_map>
#include <utility>
namespace zappyGUI {
    class Icommand;
    class GUI {
        public:
            GUI(int port, std::string hostname);

            void loop();

            Window &getWindow();
            Client &getClient();
            Game &getGame();

        private:
            void update();
            void events();
            void display();

            Window _window;
            Client _client;
            Game _game;
            std::unordered_map<std::string, std::unique_ptr<Icommand>> _commands;
            //FIXME: add the cirular buffer here
    };
};