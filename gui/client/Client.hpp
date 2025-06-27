    /*
** EPITECH PROJECT, 2024
** zap
** File description:
** Client.hpp
*/
#pragma once
#include <string>
#include "Cserver.hpp"
namespace zappyGUI {
    class Client {
        public:
            Client(int port, std::string hostname);
            ~Client();

            Cserver &getCserver();
        private:
            Cserver _Client;
            //FIXME: add the cirular buffer here

    };
};