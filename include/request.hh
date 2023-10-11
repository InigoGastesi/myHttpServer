#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
namespace http{
    class Request{
        public:
            Request(std::string request);
            ~Request();
            unsigned int getContentLength();

        private:
            std::string m_rawRequest;
            std::string m_body;
            unsigned int m_contentLength;
            std::map<std::string, std::string> m_header;
            void parseRequest();
            void addToHeader(std::string key, const std::vector<std::string> &spaces);
    };
}