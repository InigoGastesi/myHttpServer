#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <sys/socket.h>
#include <iostream>
#include <stdlib.h>

namespace http
{
    class TcpServer
    {
    public:
        TcpServer(std::string ip, int port);
        ~TcpServer();
    private:
        
    };
} // namespace http
#endif