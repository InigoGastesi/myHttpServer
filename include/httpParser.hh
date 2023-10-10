#include <string>
#include <vector>
#include <iostream>
namespace http{
    class httpParser{
        public:
            httpParser(std::string httpRequest);
            ~httpParser();

        private:
            std::string method;
            std::string URI;
            int contentLength;
            std::vector<std::string> tranferEncoding;
    };
}