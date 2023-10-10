#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX
#define BUFFER_SIZE 2048


#include <sys/socket.h>
#include <iostream>
#include <string>
#include <httpParser.hh>
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
        std::string m_ip_address;
        struct sockaddr_in m_socketAddress;
        int m_port;
        int m_socket;
        int m_new_socket;
        unsigned int m_socketAddress_len;
        int m_maxClients = 20;
        std::array<int, 20> m_clientSocket;
        int startServer();
        int acceptConnection();
        void readRequest(int socket);
        void sendResponse(int socket);
        void processRequest(int socket);
    };
} // namespace http
#endif