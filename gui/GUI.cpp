/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** GUI.cpp*
*/
#include "GUI.hpp"
#include <iostream>
#include <cstring>

zappyGUI::GUI::GUI(int port, std::string hostname): _window(), _client(port, hostname)
{
    _commands["seg"] = std::make_unique<Seg>();
    _commands["smg"] = std::make_unique<Smg>();
    _commands["tna"] = std::make_unique<Tna>();
    _commands["bct"] = std::make_unique<Bct>();
    _commands["mct"] = std::make_unique<Mct>();
    _commands["msz"] = std::make_unique<Msz>();
    _commands["suc"] = std::make_unique<Suc>();
    _commands["ebo"] = std::make_unique<Ebo>();
    _commands["edi"] = std::make_unique<Edi>();
    _commands["enw"] = std::make_unique<Enw>();
    _commands["pfk"] = std::make_unique<Pfk>();
    _commands["pbc"] = std::make_unique<Pbc>();
    _commands["pdi"] = std::make_unique<Pdi>();
    _commands["pex"] = std::make_unique<Pex>();
    _commands["pic"] = std::make_unique<Pic>();
    _commands["pie"] = std::make_unique<Pie>();
    _commands["pin"] = std::make_unique<Pin>();
    _commands["plv"] = std::make_unique<Plv>();
    _commands["pnw"] = std::make_unique<Pnw>();
    _commands["ppo"] = std::make_unique<Ppo>();
    _commands["pdr"] = std::make_unique<Pdr>();
    _commands["pgt"] = std::make_unique<Pgt>();
    _commands["sgt"] = std::make_unique<Sgt>();
    _commands["sst"] = std::make_unique<Sst>();
}

void zappyGUI::GUI::display()
{
    // FIXME: add the calls to the display of all elements of the map here
    this->_window.clear();
    this->_window.display();
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
                this->_window.close();
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
        this->_window.close();
    }
    if (pfd.revents & POLLHUP) {
        std::cerr << "Server closed" << std::endl;
        this->_window.close();
    }
    if (pfd.revents & POLLNVAL) {
        std::cerr << "invalid socket" << std::endl;
        this->_window.close();
    }
}

void zappyGUI::GUI::events()
{
    while (this->_window.pollEvent()) {
        if (this->_window.getEvent().type == sf::Event::Closed) {
            this->_window.close();
            return;
        }
        if (this->_window.getEvent().type == sf::Event::KeyPressed) {
            if (this->_window.getEvent().key.code == sf::Keyboard::Escape)
                this->_window.switchFullscreen();
        }
    }
}

void zappyGUI::GUI::loop()
{
    while (this->_window.isOpen()) {
        this->events();
        this->update();
        this->display();
    }
}

zappyGUI::Window &zappyGUI::GUI::getWindow()
{
    return this->_window;
}

zappyGUI::Client &zappyGUI::GUI::getClient()
{
    return this->_client;
}

zappyGUI::Game &zappyGUI::GUI::getGame()
{
    return this->_game;
}