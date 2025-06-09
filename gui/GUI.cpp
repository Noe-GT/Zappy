/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** GUI.cpp*
*/
#include "GUI.hpp"
#include <iostream>
#include <cstring>
#include <dirent.h>
#include <algorithm>

zappyGUI::GUI::GUI(int port, std::string hostname):
    _selectedRenderer(-1),
    _window(std::make_shared<zappyGUI::Window>()),
    _client(port, hostname),
    _game(std::make_shared<zappyGUI::Game>()),
    _renderers()
{
    printf("MAP:\nSize: %dx%d\n", this->_game->getMapSize().first, this->_game->getMapSize().second);
    this->_commands["seg"] = std::make_unique<Seg>();
    this->_commands["smg"] = std::make_unique<Smg>();
    this->_commands["tna"] = std::make_unique<Tna>();
    this->_commands["bct"] = std::make_unique<Bct>();
    this->_commands["mct"] = std::make_unique<Mct>();
    this->_commands["msz"] = std::make_unique<Msz>();
    this->_commands["suc"] = std::make_unique<Suc>();
    this->_commands["ebo"] = std::make_unique<Ebo>();
    this->_commands["edi"] = std::make_unique<Edi>();
    this->_commands["enw"] = std::make_unique<Enw>();
    this->_commands["pfk"] = std::make_unique<Pfk>();
    this->_commands["pbc"] = std::make_unique<Pbc>();
    this->_commands["pdi"] = std::make_unique<Pdi>();
    this->_commands["pex"] = std::make_unique<Pex>();
    this->_commands["pic"] = std::make_unique<Pic>();
    this->_commands["pie"] = std::make_unique<Pie>();
    this->_commands["pin"] = std::make_unique<Pin>();
    this->_commands["plv"] = std::make_unique<Plv>();
    this->_commands["pnw"] = std::make_unique<Pnw>();
    this->_commands["ppo"] = std::make_unique<Ppo>();
    this->_commands["pdr"] = std::make_unique<Pdr>();
    this->_commands["pgt"] = std::make_unique<Pgt>();
    this->_commands["sgt"] = std::make_unique<Sgt>();
    this->_commands["sst"] = std::make_unique<Sst>();
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
            renderer->initialize(this->_window, this->_game->getMapSize());
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
    this->_window->clear();
    if (this->_selectedRenderer != -1 && this->_renderers[this->_selectedRenderer] != nullptr)
        this->_game->display(this->_renderers[this->_selectedRenderer]);
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
        std::string receivedData(buffer, bytesRead);
        std::istringstream iss(receivedData);
        std::string line;

        while (std::getline(iss, line)) {
            if (!line.empty()) {
                size_t spacePos = line.find(' ');
                std::string commandName = (spacePos == std::string::npos) ? line : line.substr(0, spacePos);
                std::string args = (spacePos == std::string::npos) ? "" : line.substr(spacePos + 1);

                auto it = _commands.find(commandName);
                if (it != _commands.end()) {
                    try {
                        it->second->receive(line, *this);
                    } catch (const std::exception& e) {
                        std::cerr << "error on the " << commandName << " execution: " << e.what() << std::endl;
                    }
                } else
                    std::cerr << "unknow command: " << commandName << std::endl;
            }
        }
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
        if (this->_window->getEvent().type == sf::Event::KeyPressed) {
            if (this->_window->getEvent().key.code == sf::Keyboard::Escape)
                this->_window->switchFullscreen();
        }
    }
}

void zappyGUI::GUI::loop()
{
    while (this->_window->isOpen()) {
        this->events();
        this->update();
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

