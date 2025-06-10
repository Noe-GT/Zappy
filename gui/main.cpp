/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** gui/main.cpp
*/
#include "GUI.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

void exitWithUsage(int exitCode = 84)
{
    std::cerr << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    exit(exitCode);
}

int main(int argc, char **argv)
{
	int port = -1;
	std::string hostname;

	if (argc != 5)
        exitWithUsage();
    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-p") == 0) {
            if (i + 1 >= argc)
                exitWithUsage();
            port = std::atoi(argv[++i]);
            if (port <= 0) {
                std::cerr << "Error: Invalid port number" << std::endl;
				return 84;
            }
        }
        else if (std::strcmp(argv[i], "-h") == 0) {
            if (i + 1 >= argc)
                exitWithUsage();
            hostname = argv[++i];
        }
        else
            exitWithUsage();
    }
    try {
        zappyGUI::GUI gui(port, hostname);
        gui.loop();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}