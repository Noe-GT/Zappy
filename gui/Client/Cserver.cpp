/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Cserver.cpp
*/


#include "Cserver.hpp"

Cserver::Cserver(int port)
{
    init(port);
}

Cserver::~Cserver()
{
}

Cserver::Cserver()
{
}

void Cserver::init(int port)
{
    this->_adress.sin_family = AF_INET;
    this->_adress.sin_port = htons(port);
    this->_adress.sin_addr.s_addr = INADDR_ANY;
}

int Cserver::poll(pollfd *__fds, nfds_t __nfds, int __timeout)
{
    return ::poll(__fds, __nfds, __timeout);
}

int Cserver::bind(int __fd, const sockaddr *__addr, socklen_t __len) noexcept
{
    return ::bind(__fd, __addr, __len);
}
int Cserver::bind(int __fd)
{
    return ::bind(__fd, (struct sockaddr *)&this->_adress, sizeof(this->_adress));
}

int Cserver::listen(int __fd, int __n) noexcept
{
    return ::listen(__fd, __n);
}

int Cserver::socket(int __domain, int __type, int __protocol) noexcept
{
    return ::socket(__domain, __type, __protocol);
}

int Cserver::accept(int __fd, sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len)
{
    return ::accept(__fd, __addr, __addr_len);
}

int Cserver::accept(int __fd)
{
    socklen_t addr_len = sizeof(_adress);
    return ::accept(__fd, (struct sockaddr *)&_adress, &addr_len);
}

int Cserver::connect(int __fd, const sockaddr *__addr, socklen_t __len)
{
    return ::connect(__fd, __addr, __len);
}

int Cserver::connect(int __fd)
{
    socklen_t addr_len = sizeof(_adress);
    return ::connect(__fd, (struct sockaddr *)&_adress, addr_len);
}

int Cserver::send(int fd, const char *format, ...)
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

void Cserver::setSocket(int newSocket)
{
    this->_socket = newSocket;
}

int Cserver::getSocket()
{
    return this->_socket;
}

void Cserver::setAdress(struct sockaddr_in newAdress)
{
    this->_adress = newAdress;
}

struct sockaddr_in &Cserver::getAdress()
{
    return this->_adress;
}
