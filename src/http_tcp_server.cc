#include <http_tcp_server.h>
#include <iostream>
#include <sstream>
#include <unistd.h>


namespace{
    void log(const std::string &messagge){
        std::cout << messagge << std::endl;
    }

    void exitWithError(const std::string &errorMessage){
        log("ERROR:" + errorMessage);
        exit(1);
    }
}


namespace http
{
    TcpServer::TcpServer(std::string ip_address, int port) : 
        m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(),
        m_socketAddress_len(sizeof(m_socketAddress))
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
        m_threadPool.reserve(10);
        startServer();
    }
    TcpServer::~TcpServer()
    {
        close(m_socket);
        exit(0);
    }

    int TcpServer::startServer(){
        std::cout << m_ip_address << std::endl;
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0){
            exitWithError("Cannot create socket");
            return 1;
        }


        if (bind(m_socket, (sockaddr *) &m_socketAddress, m_socketAddress_len) < 0){
            exitWithError("Cannot connect socket to address");
            return 1;
        }
        return 0;
    }

    void TcpServer::startListen(){
        
        if (listen(m_socket, 20) < 0){
            exitWithError("Socket listen failed");
        }
        std::ostringstream ss;
        ss << "\n** Listening on ADRESS: "
        << inet_ntoa(m_socketAddress.sin_addr)
        << " PORT: " << ntohs(m_socketAddress.sin_port)
        << "***\n\n";
        log(ss.str());
        fd_set readfds;
        int max_sd;
        int sd;
        int activity;
        for(int i = 0; i < m_maxClients; i++){
            m_clientSocket[i] = 0;
        }
        while(true){
            FD_ZERO(&readfds);
            FD_SET(m_socket, &readfds);
            max_sd = m_socket;
            for(int i = 0; i < m_maxClients; i++){
                sd = m_clientSocket[i];

                if (sd > 0)
                    FD_SET(sd, &readfds);
                if(sd > max_sd)
                    max_sd = sd;
            }
            activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
            // m_new_socket = acceptConnection();
            std::cout << "incoming connection" << std::endl;

        }
    }

    int TcpServer::acceptConnection(){
        int new_socket = accept(m_socket, (sockaddr * ) &m_socketAddress, &m_socketAddress_len);
        if (new_socket < 0){
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
            exitWithError(ss.str());
        }
        return new_socket;
    }

    void TcpServer::readRequest(int socket){
        char buffer[BUFFER_SIZE];
        int bytesReceived = read(socket, buffer, BUFFER_SIZE);
        if(bytesReceived < 0){
            exitWithError("Failed reading the request");
        }
        sleep(3);
        std::string request(buffer);
        std::cout << request << std::endl;

    }

}