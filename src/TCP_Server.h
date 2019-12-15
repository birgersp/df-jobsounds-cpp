#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "TCP_Connection.h"
#include "core.h"
#include <string>
#include <Winsock2.h>
#include <ws2tcpip.h>

class TCP_Server
{
public:
    TCP_Server();
    ~TCP_Server();

    void bind(int port);
    bool is_bound();

    TCP_Connection accept_connection();

private:
    struct sockaddr_in socket_address;
    SOCKET listen_socket = INVALID_SOCKET;
};

#endif // TCP_SERVER_H
