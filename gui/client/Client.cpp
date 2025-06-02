/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include <stdexcept>
zappyGUI::Client::Client(int port, std::string hostname): _Client(port)
{
    int sockfd = _Client.socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
        throw std::runtime_error("Socket creation failed");
    if (!hostname.empty()) {
        inet_pton(AF_INET, hostname.c_str(), &_Client.getAdress().sin_addr);
    }
    if (_Client.connect(sockfd) == -1) {
        close(sockfd);
        throw std::runtime_error("Connection to server failed");
    }
    this->_Client.setSocket(sockfd);
}

zappyGUI::Client::~Client()
{
}

zappyGUI::Cserver &zappyGUI::Client::getCserver()
{
    return this->_Client;
}
