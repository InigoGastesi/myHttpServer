#include <string>
#include <map>

namespace http
{
    class Response
    {
        public:
            Response();
            ~Response();
            std::map<std::string, std::string> header;
            void addStringToBody(std::string body);
            
        private:
            std::string m_body;
    };
}