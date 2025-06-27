/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.hpp
*/

#pragma once
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
#include "client/commands/misc/WELCOME.hpp"
#include "client/commands/misc/Suc.hpp"
#include "client/commands/misc/WELCOME.hpp"
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
#include "DlLoader.hpp"
#include "UI/shared/IGraphical.hpp"

extern "C" {
    #include "../protocol/include/protocol.h"
}

namespace zappyGUI {
    class Icommand;
    class GUI {
        public:
            GUI(int port, std::string hostname);

            void loop();

            std::shared_ptr<zappyGUI::Window> &getWindow();
            Client &getClient();
            std::shared_ptr<zappyGUI::Game> &getGame();
            DLLoader &getLoader();
            std::vector<std::shared_ptr<IGraphical>> &getRenderers();

        private:
            void update();
            void events();
            void display();

            int _selectedRenderer;
            std::shared_ptr<zappyGUI::Window> _window;
            Client _client;
            std::shared_ptr<zappyGUI::Game> _game;
            std::vector <std::shared_ptr<zappyGUI::IGraphical>> _renderers;
            std::unordered_map<std::string, std::shared_ptr<Icommand>> _commands;
            std::vector<std::shared_ptr<UIBlocks::IUIBlock>> _elements;
            std::shared_ptr<circular_buffer_t> _circularBuffer;
    };
};