#include <http_tcp_server.h>

namespace http
{
    TcpServer::TcpServer(std::string ip, int port)
    {
        int m_socket = socket(AF_INET, SOCK_STREAM, 0);
        ;
    }
    TcpServer::~TcpServer()
    {
        
    }
}