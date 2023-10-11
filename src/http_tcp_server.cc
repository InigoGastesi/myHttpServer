#include <http_tcp_server.hh>
#include <iostream>
#include <sstream>
#include <unistd.h>

namespace
{
    void log(const std::string &messagge)
    {
        std::cout << messagge << std::endl;
    }

    void exitWithError(const std::string &errorMessage)
    {
        log("ERROR:" + errorMessage);
        exit(1);
    }
}

namespace http
{
    TcpServer::TcpServer(std::string ip_address, int port) : m_ipAddress(ip_address), m_port(port), m_socket(), m_newSocket(),
                                                             m_socketAddress_len(sizeof(m_socketAddress))
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
        startServer();
    }
    TcpServer::~TcpServer()
    {
        close(m_socket);
        exit(0);
    }

    int TcpServer::startServer()
    {
        std::cout << m_ipAddress << std::endl;
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            exitWithError("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
        {
            exitWithError("Cannot connect socket to address");
            return 1;
        }
        return 0;
    }

    void TcpServer::startListen()
    {

        if (listen(m_socket, 20) < 0)
        {
            exitWithError("Socket listen failed");
        }
        std::ostringstream ss;
        ss << "\n** Listening on ADRESS: "
           << inet_ntoa(m_socketAddress.sin_addr)
           << " PORT: " << ntohs(m_socketAddress.sin_port)
           << "***\n\n";
        log(ss.str());
        int new_socket;
        while (true)
        {
            new_socket = acceptConnection();
            std::thread t(&TcpServer::processRequest, this, new_socket);
            t.detach();
        }
    }

    int TcpServer::acceptConnection()
    {
        int new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
        if (new_socket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
            exitWithError(ss.str());
        }
        return new_socket;
    }

    void TcpServer::processRequest(int socket)
    {
        readRequest(socket);
        sendResponse(socket);
        close(socket);
    }

    void TcpServer::readRequest(int socket)
    {
        char buffer[BUFFER_SIZE];
        int bytesReceived = -1;
        int readedBuffer = 0;
        unsigned int contentLength;
        bytesReceived = read(socket, buffer, BUFFER_SIZE);
        readedBuffer += BUFFER_SIZE;
        if (bytesReceived < 0)
        {
            exitWithError("Failed reading the request");
        }
        std::string request(buffer);
        Request req = Request(request);
        contentLength = req.getContentLength();
        std::cout << request << std::endl;

        while (readedBuffer < contentLength && contentLength != 0)
        {
            bytesReceived = read(socket, buffer, BUFFER_SIZE);
            readedBuffer += BUFFER_SIZE;
            if (bytesReceived < 0)
            {
                exitWithError("Failed reading the request");
            }
            std::string request(buffer);
            req.addBufferToBody(request);
            std::cout << request << std::endl;
        } 
    }


    void TcpServer::sendResponse(int socket)
    {
        Response res = Response();
        res.writeHtmlInBody("/index.html");
        std::string strRes = res.responseToString(200);
        long byteSent = write(socket, strRes.c_str(), strRes.size());

        if (byteSent == strRes.size())
        {
            log("------ Server Response sent to client ------\n\n");
        }
        else
        {
            log("Error sending response to client");
        }
    }
}