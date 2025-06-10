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
        // for (auto &element : this->_elements) {
        //     element->handleEvent(this->_window.getEvent(), this->_window);
        // }
        
    }
}

void zappyGUI::GUI::loop()
{
    // std::shared_ptr<UIBlocks::IUIBlock> player1 = std::make_shared<UIBlocks::Text>("Dembele", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player2 = std::make_shared<UIBlocks::Text>("Yamal", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player3 = std::make_shared<UIBlocks::Text>("Mbappe", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player4 = std::make_shared<UIBlocks::Text>("Doue", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player5 = std::make_shared<UIBlocks::Text>("Pogba", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player6 = std::make_shared<UIBlocks::Text>("Kante", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player7 = std::make_shared<UIBlocks::Text>("Messi", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player8 = std::make_shared<UIBlocks::Text>("Ronaldo", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player9 = std::make_shared<UIBlocks::Text>("Maradona", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> player10 = std::make_shared<UIBlocks::Text>("Pele", std::pair<float, float>(0, 0), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank1 = std::make_shared<UIBlocks::Text>("1.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank2 = std::make_shared<UIBlocks::Text>("2.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank3 = std::make_shared<UIBlocks::Text>("3.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank4 = std::make_shared<UIBlocks::Text>("4.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank5 = std::make_shared<UIBlocks::Text>("5.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank6 = std::make_shared<UIBlocks::Text>("6.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank7 = std::make_shared<UIBlocks::Text>("7.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank8 = std::make_shared<UIBlocks::Text>("8.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank9 = std::make_shared<UIBlocks::Text>("9.", std::pair<float, float>(550, 650), 50);
    // std::shared_ptr<UIBlocks::IUIBlock> rank10 = std::make_shared<UIBlocks::Text>("10.", std::pair<float, float>(550, 650), 50);

    // auto pair_value1 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank1, player1);
    // std::shared_ptr<UIBlocks::Pair> pair1 = std::make_shared<UIBlocks::Pair>(pair_value1, std::pair<float, float>(0, 0));
    // auto pair_value2 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank2, player2);
    // std::shared_ptr<UIBlocks::Pair> pair2 = std::make_shared<UIBlocks::Pair>(pair_value2, std::pair<float, float>(0, 0));
    // auto pair_value3 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank3, player3);
    // std::shared_ptr<UIBlocks::Pair> pair3 = std::make_shared<UIBlocks::Pair>(pair_value3, std::pair<float, float>(0, 0));
    // auto pair_value4 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank4, player4);
    // std::shared_ptr<UIBlocks::Pair> pair4 = std::make_shared<UIBlocks::Pair>(pair_value4, std::pair<float, float>(0, 0));
    // auto pair_value5 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank5, player5);
    // std::shared_ptr<UIBlocks::Pair> pair5 = std::make_shared<UIBlocks::Pair>(pair_value5, std::pair<float, float>(0, 0));
    // auto pair_value6 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank6, player6);
    // std::shared_ptr<UIBlocks::Pair> pair6 = std::make_shared<UIBlocks::Pair>(pair_value6, std::pair<float, float>(0, 0));
    // auto pair_value7 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank7, player7);
    // std::shared_ptr<UIBlocks::Pair> pair7 = std::make_shared<UIBlocks::Pair>(pair_value7, std::pair<float, float>(0, 0));
    // auto pair_value8 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank8, player8);
    // std::shared_ptr<UIBlocks::Pair> pair8 = std::make_shared<UIBlocks::Pair>(pair_value8, std::pair<float, float>(0, 0));
    // auto pair_value9 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank9, player9);
    // std::shared_ptr<UIBlocks::Pair> pair9 = std::make_shared<UIBlocks::Pair>(pair_value9, std::pair<float, float>(0, 0));
    // auto pair_value10 = std::pair<std::shared_ptr<UIBlocks::IUIBlock>, std::shared_ptr<UIBlocks::IUIBlock>>(rank10, player10);
    // std::shared_ptr<UIBlocks::Pair> pair10 = std::make_shared<UIBlocks::Pair>(pair_value10, std::pair<float, float>(0, 0));

    // std::vector<std::shared_ptr<UIBlocks::IUIBlock>> options = {
    //     pair1, pair2, pair3, pair4, pair5,
    //     pair6, pair7, pair8, pair9, pair10
    // };
    // std::shared_ptr<UIBlocks::List> list = std::make_shared<UIBlocks::List>(options, std::pair<float, float>(1300, 200), std::pair<float, float>(100, 200));
    // std::shared_ptr<UIBlocks::PopupSelector> selector = std::make_shared<UIBlocks::PopupSelector>(options, std::pair<float, float>(500, 200));
    // selector.get()->open();
    // std::shared_ptr<UIBlocks::Timer> timer = std::make_shared<UIBlocks::Timer>(std::pair<float, float>(20, 20), 30);
    // timer.get()->start();
    // std::shared_ptr<UIBlocks::Text> title = std::make_shared<UIBlocks::Text>("Level 5", std::pair<float, float>(700, 20), 50);
    // std::shared_ptr<UIBlocks::Text> selected = std::make_shared<UIBlocks::Text>("Empty", std::pair<float, float>(700, 800), 50);
    // std::string alternativeText = "Rickroll";
    // std::shared_ptr<UIBlocks::Image> rickroll = std::make_shared<UIBlocks::Image>("gui/UI/shared/UIBlocks/assets/Rickrolling.png", std::pair<float, float>(20, 500), std::pair<float, float>(584, 729), alternativeText);
    // this->_elements.push_back(selector);
    // this->_elements.push_back(timer);
    // this->_elements.push_back(list);
    // this->_elements.push_back(title);
    // this->_elements.push_back(selected);
    // this->_elements.push_back(rickroll);
    while (this->_window.isOpen()) {
        // if (selector.get()->getSelected() != nullptr && std::holds_alternative<std::string>(std::get<std::vector<std::shared_ptr<UIBlocks::IUIBlock>>>(selector.get()->getSelected()->getValue()).at(1).get()->getValue()))
        //     selected.get()->setText("Selected: " + std::get<std::string>(std::get<std::vector<std::shared_ptr<UIBlocks::IUIBlock>>>(selector.get()->getSelected()->getValue()).at(1).get()->getValue()));
        this->_window.clear();
        this->events();
        
        this->update();
        for (auto &element : this->_elements)
            element->draw(this->_window);
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