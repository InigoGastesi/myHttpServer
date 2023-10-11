#include <response.hh>


namespace http
{
    Response::Response()
    {
        header.insert(std::pair<std::string,std::string>("Accept-Charset", "" ));
        header.insert(std::pair<std::string,std::string>("Accept-Language", "")); 
        header.insert(std::pair<std::string,std::string>("Allow", "")); 
        header.insert(std::pair<std::string,std::string>("Authorization", "")); 
        header.insert(std::pair<std::string,std::string>("Content-Language", "")); 
        header.insert(std::pair<std::string,std::string>("Content-Length", "")); 
        header.insert(std::pair<std::string,std::string>("Content-Location", "")); 
        header.insert(std::pair<std::string,std::string>("Content-Type", "")); 
        header.insert(std::pair<std::string,std::string>("Date", "")); 
        header.insert(std::pair<std::string,std::string>("Host", "")); 
        header.insert(std::pair<std::string,std::string>("Last-Modified", "")); 
        header.insert(std::pair<std::string,std::string>("Location", "")); 
        header.insert(std::pair<std::string,std::string>("Referer", "")); 
        header.insert(std::pair<std::string,std::string>("Retry-After", "")); 
        header.insert(std::pair<std::string,std::string>("Server", "")); 
        header.insert(std::pair<std::string,std::string>("Transfer-Encoding", "")); 
        header.insert(std::pair<std::string,std::string>("User-Agent", "")); 
        header.insert(std::pair<std::string,std::string>("WWW-Authenticate", ""));
    }
    Response::~Response()
    {

    }

    void Response::addStringToBody(std::string body)
    {
        m_body += body;
    }
}

