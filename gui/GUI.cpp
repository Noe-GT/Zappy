/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.cpp
*/
#include "GUI.hpp"
#include <iostream>
#include <cstring>

zappyGUI::GUI::GUI(int port, std::string hostname): _window(), _client(port, hostname)
{
    _commands["Seg"] = std::move(std::make_unique <Seg>(Seg()));
    _commands["Smg"] = std::move(std::make_unique <Smg>(Smg()));
    _commands["Tna"] = std::move(std::make_unique <Tna>(Tna()));
    _commands["Bct"] = std::move(std::make_unique <Bct>(Bct()));
    _commands["Mct"] = std::move(std::make_unique <Mct>(Mct()));
    _commands["Msz"] = std::move(std::make_unique <Msz>(Msz()));
    _commands["Suc"] = std::move(std::make_unique <Suc>(Suc()));
    _commands["Ebo"] = std::move(std::make_unique <Ebo>(Ebo()));
    _commands["Edi"] = std::move(std::make_unique <Edi>(Edi()));
    _commands["Enw"] = std::move(std::make_unique <Enw>(Enw()));
    _commands["Pfk"] = std::move(std::make_unique <Pfk>(Pfk()));
    _commands["Pbc"] = std::move(std::make_unique <Pbc>(Pbc()));
    _commands["Pdi"] = std::move(std::make_unique <Pdi>(Pdi()));
    _commands["Pex"] = std::move(std::make_unique <Pex>(Pex()));
    _commands["Pic"] = std::move(std::make_unique <Pic>(Pic()));
    _commands["Pie"] = std::move(std::make_unique <Pie>(Pie()));
    _commands["Pin"] = std::move(std::make_unique <Pin>(Pin()));
    _commands["Plv"] = std::move(std::make_unique <Plv>(Plv()));
    _commands["Pnw"] = std::move(std::make_unique <Pnw>(Pnw()));
    _commands["Ppo"] = std::move(std::make_unique <Ppo>(Ppo()));
    _commands["Pdr"] = std::move(std::make_unique <Pdr>(Pdr()));
    _commands["Pgt"] = std::move(std::make_unique <Pgt>(Pgt()));
    _commands["Sgt"] = std::move(std::make_unique <Sgt>(Sgt()));
    _commands["Sst"] = std::move(std::make_unique <Sst>(Sst()));
}

void zappyGUI::GUI::display()
{
    this->_window.display();
    //FIXME: add the calls to the display of all elements of the map here
}

void zappyGUI::GUI::update()
{
    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, BUFFER_SIZE);
    ssize_t bytesRead = read(this->getClient().getCserver().getSocket(), buffer, BUFFER_SIZE - 1);
    std::string receivedData(buffer, bytesRead);
    std::istringstream iss(receivedData);
    std::string line;

    if (bytesRead <= 0) {
        if (bytesRead == 0)
            std::cerr << "Connexion fermée par le client" << std::endl;
        else
            perror("Erreur de lecture");
        return;
    }
    while (std::getline(iss, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!line.empty()) {
            size_t spacePos = line.find(' ');
            std::string commandName = (spacePos == std::string::npos) ? line : line.substr(0, spacePos);
            std::string args = (spacePos == std::string::npos) ? "" : line.substr(spacePos + 1);
            auto it = _commands.find(commandName);
            if (it != _commands.end()) {
                try {
                    it->second->receive(line, *this);
                } catch (const std::exception& e) {
                    std::cerr << "Erreur d'exécution de la commande " << commandName << ": " << e.what() << std::endl;
                }
            } else
                std::cerr << "Commande inconnue: " << commandName << std::endl;
        }
    }
}

void zappyGUI::GUI::events()
{
    while (this->_window.pollEvent(this->_window.getEvent())) {
        if (this->_window.getEvent().type == sf::Event::Closed)
            exit(0);
        if (this->_window.getEvent().type == sf::Event::KeyPressed && this->_window.getEvent().key.code == sf::Keyboard::Escape)
            this->_window.switchFullscreen();
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

zappyGUI::window zappyGUI::GUI::getWindow()
{
    return this->_window;
}

zappyGUI::Client zappyGUI::GUI::getClient()
{
    return this->_client;
}

zappyGUI::Game zappyGUI::GUI::getGame()
{
    return this->_game;
}