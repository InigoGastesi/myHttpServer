#include <iostream>
#include <string>
#include <http_tcp_server.hh>

int main(int argc, char* argv[]){
    using namespace http;
    TcpServer server = TcpServer("0.0.0.0",8080);
    server.startListen();
    std::cout << "finish" << std::endl;

}