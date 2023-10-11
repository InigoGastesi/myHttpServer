#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
namespace http
{
    class Response
    {
        public:
            Response();
            ~Response();
            std::map<std::string, std::string> header;
            void addStringToBody(std::string body);
            std::string responseToString(unsigned int code);
            void writeHtmlInBody(std::string URI);
            
        private:
            std::string m_body;
            
    };
}