/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** network_utils
*/

#include "network.h"

struct sockaddr_in *make_addr(int port)
{
    struct sockaddr_in *addr;

    addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
    return addr;
}

static int socket_listen(int sockfd, int listen_n)
{
    if (listen(sockfd, listen_n) < 0) {
        perror("Socket_listen");
        return -1;
    }
    return sockfd;
}

int create_socket(struct sockaddr_in *addr, socklen_t addrlen, int listen_n)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int on = 1;

    if (sockfd < 0) {
        perror("socket creation failed");
        return -1;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
        (char *)&on, sizeof(on)) < 0) {
            perror("setsockopt() failed");
            close(sockfd);
            return -1;
    }
    if (bind(sockfd, (struct sockaddr*)addr, addrlen) < 0) {
        perror("Bind failed");
        close(sockfd);
        return -1;
    }
    return socket_listen(sockfd, listen_n);
}
