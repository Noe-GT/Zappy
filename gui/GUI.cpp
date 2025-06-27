/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** GUI.cpp*
*/
#include "GUI.hpp"
#include <iostream>
#include <cstring>
#include "UI/shared/UIBlocks/PopupSelector/PopupSelector.hpp"
#include "UI/shared/UIBlocks/Text/Text.hpp"
#include "UI/shared/UIBlocks/Timer/Timer.hpp"
#include "UI/shared/UIBlocks/List/List.hpp"
#include "UI/shared/UIBlocks/Pair/Pair.hpp"
#include "UI/shared/UIBlocks/Image/Image.hpp"

#include <dirent.h>
#include <algorithm>

zappyGUI::GUI::GUI(int port, std::string hostname):
    _selectedRenderer(-1),
    _window(std::make_shared<zappyGUI::Window>()),
    _client(port, hostname),
    _game(std::make_shared<zappyGUI::Game>()),
    _renderers(),
    _circularBuffer(create_buffer(), destroy_buffer)
{
    this->_commands["seg"] = std::make_shared<Seg>();
    this->_commands["smg"] = std::make_shared<Smg>();
    this->_commands["tna"] = std::make_shared<Tna>();
    this->_commands["bct"] = std::make_shared<Bct>();
    this->_commands["mct"] = std::make_shared<Mct>();
    this->_commands["msz"] = std::make_shared<Msz>();
    this->_commands["suc"] = std::make_shared<Suc>();
    this->_commands["ebo"] = std::make_shared<Ebo>();
    this->_commands["edi"] = std::make_shared<Edi>();
    this->_commands["enw"] = std::make_shared<Enw>();
    this->_commands["pfk"] = std::make_shared<Pfk>();
    this->_commands["pbc"] = std::make_shared<Pbc>();
    this->_commands["pdi"] = std::make_shared<Pdi>();
    this->_commands["pex"] = std::make_shared<Pex>();
    this->_commands["pic"] = std::make_shared<Pic>();
    this->_commands["pie"] = std::make_shared<Pie>();
    this->_commands["pin"] = std::make_shared<Pin>();
    this->_commands["plv"] = std::make_shared<Plv>();
    this->_commands["pnw"] = std::make_shared<Pnw>();
    this->_commands["ppo"] = std::make_shared<Ppo>();
    this->_commands["pdr"] = std::make_shared<Pdr>();
    this->_commands["pgt"] = std::make_shared<Pgt>();
    this->_commands["sgt"] = std::make_shared<Sgt>();
    this->_commands["sst"] = std::make_shared<Sst>();
    this->_commands["WELCOME"] = std::make_shared<WELCOME>();
    const std::string pluginsDir = "./gui/plugins";
    DIR* dir = opendir(pluginsDir.c_str());

    if (!dir) {
        std::cerr << "Failed to open plugins directory: " << pluginsDir << std::endl;
        return;
    }

    dirent* dirent;
    while ((dirent = readdir(dir)) != nullptr) {
        std::string filename(dirent->d_name);
        if (filename == "." || filename == "..")
            continue;
        std::string fullPath = pluginsDir + "/" + filename;
        try {
            DLLoader pluginLoader(fullPath);
            auto renderer = pluginLoader.getInstance<IGraphical>("entryPoint");
            renderer->initialize(std::make_shared<zappyGUI::GUI> (*this));
            this->_renderers.push_back(std::move(renderer));
            std::cout << "loaded " << filename << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Failed to load plugin " << filename << ": " << e.what() << std::endl;
        }
    }
    closedir(dir);
    if (!this->_renderers.empty())
        this->_selectedRenderer = 0;
}

void zappyGUI::GUI::display()
{
    // FIXME: add the calls to the display of all elements of the map here
    if (this->_selectedRenderer != -1 && this->_renderers[this->_selectedRenderer] != nullptr) {
        this->_game->display(this->_renderers[this->_selectedRenderer]);
    }
    this->_window->display();
}

void zappyGUI::GUI::update()
{
    int socket_fd = this->getClient().getCserver().getSocket();
    struct pollfd pfd;
    pfd.fd = socket_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    int result = poll(&pfd, 1, 0);
    if (result <= 0)
        return;
    if (pfd.revents & POLLIN) {
        const int BUFFER_SIZE = 4096;
        char buffer[BUFFER_SIZE];
        std::memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytesRead = read(socket_fd, buffer, BUFFER_SIZE - 1);

        if (bytesRead <= 0) {
            if (bytesRead == 0) {
                std::cerr << "Connexion fermée par le serveur" << std::endl;
                this->_window->close();
            }
            return;
        }
        write_string(this->_circularBuffer.get(), buffer);
        char* line;
        while ((line = read_string(this->_circularBuffer.get())) != nullptr) {
            std::string strLine(line);
            free_str(line);
            if (!strLine.empty()) {
                size_t spacePos = strLine.find(' ');
                std::string commandName = (spacePos == std::string::npos) ? strLine : strLine.substr(0, spacePos);
                // std::clog << commandName.length() << std::endl;
                if (commandName.back() == '\n')
                commandName.pop_back();
                std::string args = (spacePos == std::string::npos) ? "" : strLine.substr(spacePos + 1);
                auto it = _commands.find(commandName);
                if (it != _commands.end()) {
                    try {
                        std::clog << strLine << std::endl;
                        it->second->receive(strLine, *this);
                    } catch (const std::exception& e) {
                        std::cerr << "error on the " << commandName << " execution: " << e.what() << std::endl;
                    }
                } else {
                    std::cerr << "unknow command: " << commandName << std::endl;
                }
            }
        }
        // this->_circularBuffer.get() = clean_buffer(this->_circularBuffer.get());
    }
    if (pfd.revents & POLLERR) {
        std::cerr << "error detected on the socket" << std::endl;
        this->_window->close();
    }
    if (pfd.revents & POLLHUP) {
        std::cerr << "Server closed" << std::endl;
        this->_window->close();
    }
    if (pfd.revents & POLLNVAL) {
        std::cerr << "invalid socket" << std::endl;
        this->_window->close();
    }
}

void zappyGUI::GUI::events()
{
    while (this->_window->pollEvent()) {
        if (this->_window->getEvent().type == sf::Event::Closed) {
            this->_window->close();
            return;
        }
        if (this->_window->getEvent().type == sf::Event::KeyPressed ||
            this->_window->getEvent().type == sf::Event::MouseButtonPressed) {
            if (this->_window->getEvent().key.code == sf::Keyboard::Space)
                this->_window->switchFullscreen();
            else {
                if (this->_selectedRenderer != -1 && this->_renderers[this->_selectedRenderer] != nullptr)
                    this->_renderers[this->_selectedRenderer]->handleEvents();
            }
        }
        this->_game->handleUIEvents(this->_window->getEvent(), this->_window);
    }
}

void zappyGUI::GUI::loop()
{
    while (this->_window->isOpen()) {
        this->_window->clear();
        this->events();
        this->update();
        for (auto &element : this->_elements)
            element->draw(this->_window);
        this->display();
    }
}

std::shared_ptr<zappyGUI::Window> &zappyGUI::GUI::getWindow()
{
    return this->_window;
}

zappyGUI::Client &zappyGUI::GUI::getClient()
{
    return this->_client;
}

std::shared_ptr<zappyGUI::Game> &zappyGUI::GUI::getGame()
{
    return this->_game;
}

std::vector <std::shared_ptr<zappyGUI::IGraphical>> &zappyGUI::GUI::getRenderers()
{
    return this->_renderers;
}

