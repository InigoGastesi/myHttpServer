#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX
#define BUFFER_SIZE 2048


#include <sys/socket.h>
#include <iostream>
#include <response.hh>
#include <string>
#include <request.hh>
#include <thread>
#include <arpa/inet.h>
#include <vector>
#ifdef __linux__
#include <linux/in.h>
#endif
namespace http
{
    class TcpServer
    {
    public:
        TcpServer(std::string ip_address, int port);
        ~TcpServer();
        void startListen();
    private:
        std::string m_ipAddress;
        struct sockaddr_in m_socketAddress;
        int m_port;
        int m_socket;
        int m_newSocket;
        unsigned int m_socketAddress_len;
        int m_maxClients = 20;
        int startServer();
        int acceptConnection();
        void readRequest(int socket);
        void sendResponse(int socket);
        void processRequest(int socket);
    };
} // namespace http
#endif