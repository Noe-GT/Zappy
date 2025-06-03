/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Cserver.cpp
*/


#include "Cserver.hpp"

zappyGUI::Cserver::Cserver(int port)
{
    init(port);
}

zappyGUI::Cserver::~Cserver()
{
}

zappyGUI::Cserver::Cserver()
{
}

void zappyGUI::Cserver::init(int port)
{
    this->_adress.sin_family = AF_INET;
    this->_adress.sin_port = htons(port);
    this->_adress.sin_addr.s_addr = INADDR_ANY;
}

int zappyGUI::Cserver::poll(pollfd *__fds, nfds_t __nfds, int __timeout)
{
    return ::poll(__fds, __nfds, __timeout);
}

int zappyGUI::Cserver::bind(int __fd, const sockaddr *__addr, socklen_t __len)
{
    return ::bind(__fd, __addr, __len);
}
int zappyGUI::Cserver::bind(int __fd)
{
    return ::bind(__fd, (struct sockaddr *)&this->_adress, sizeof(this->_adress));
}

int zappyGUI::Cserver::listen(int __fd, int __n)
{
    return ::listen(__fd, __n);
}

int zappyGUI::Cserver::socket(int __domain, int __type, int __protocol)
{
    return ::socket(__domain, __type, __protocol);
}

int zappyGUI::Cserver::accept(int __fd, sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len)
{
    return ::accept(__fd, __addr, __addr_len);
}

int zappyGUI::Cserver::accept(int __fd)
{
    socklen_t addr_len = sizeof(_adress);
    return ::accept(__fd, (struct sockaddr *)&_adress, &addr_len);
}

int zappyGUI::Cserver::connect(int __fd, const sockaddr *__addr, socklen_t __len)
{
    return ::connect(__fd, __addr, __len);
}

int zappyGUI::Cserver::connect(int __fd)
{
    socklen_t addr_len = sizeof(_adress);
    return ::connect(__fd, (struct sockaddr *)&_adress, addr_len);
}

int zappyGUI::Cserver::send(int fd, const char *format, ...)
{
    va_list args;
    char *buff = NULL;
    int len;
    int witenNbr;

    va_start(args, format);
    len = vasprintf(&buff, format, args);
    va_end(args);
    if (len < 0 || !buff || fd == -1)
        return -1;
    witenNbr = write(fd, buff, len);
    free(buff);
    if (witenNbr < 0)
        return -1;
    return witenNbr;
}

int zappyGUI::Cserver::send(const char *format, ...)
{
    va_list args;
    char *buff = NULL;
    int len;
    int witenNbr;
    pollfd pfd = {this->_socket, POLLOUT, 0};

    if (this->poll(&pfd, 1, 100) <= 0 || !(pfd.revents & POLLOUT))
        return -1;
    va_start(args, format);
    len = vasprintf(&buff, format, args);
    va_end(args);
    if (len < 0 || !buff || this->_socket == -1)
        return -1;
    witenNbr = write(this->_socket, buff, len);
    free(buff);
    if (witenNbr < 0)
        return -1;
    return witenNbr;
}


void zappyGUI::Cserver::setSocket(int newSocket)
{
    this->_socket = newSocket;
}

int zappyGUI::Cserver::getSocket()
{
    return this->_socket;
}

void zappyGUI::Cserver::setAdress(struct sockaddr_in newAdress)
{
    this->_adress = newAdress;
}

struct sockaddr_in &zappyGUI::Cserver::getAdress()
{
    return this->_adress;
}