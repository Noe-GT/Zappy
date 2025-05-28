/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Cserver.hpp
*/

#pragma once
#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

class Cserver
{
    public:
        Cserver();
        Cserver(int port);
        ~Cserver();

        void init(int port);
        int poll(pollfd *__fds, nfds_t __nfds, int __timeout);
        int bind(int __fd, const sockaddr *__addr, socklen_t __len);
        int bind(int __fd);
        int listen(int __fd, int __n);
        int socket(int __domain, int __type, int __protocol);
        int accept(int __fd, sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len);
        int accept(int __fd);
        int connect(int __fd, const sockaddr *__addr, socklen_t __len);
        int connect(int __fd);
        int send(int fd, const char *format, ...);

        void setSocket(int newSocket);
        int getSocket();
        void setAdress(struct sockaddr_in newAdress);
        struct sockaddr_in &getAdress();
    private:
        struct sockaddr_in _adress;
        int _socket;
};
