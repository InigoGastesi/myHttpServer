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
        header.insert(std::pair<std::string,std::string>("Content-Length", "0")); 
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
        header["Content-Length"] = std::to_string(m_body.size());
    }

    std::string Response::responseToString(unsigned int code)
    {
        std::stringstream ss;
        ss << "HTTP/1.1 " << code << " OK" << "\r\n";
        for (auto param : header)
        {
            ss << param.first << ": " << param.second << "\r\n";
        }
        ss << "\r\n";
        if(stoi(header["Content-Length"]) > 0)
        {
            ss << m_body;
        }
        return ss.str();
    }

    void Response::writeHtmlInBody(std::string URI)
    {
        std::fstream htmlFile;
        header["Content-Type"] = "text/html";
        htmlFile.open("../www"+URI, std::ios::in);
        if (htmlFile.is_open())
        {
            std::string temp;
            while(getline(htmlFile, temp))
            {
                addStringToBody(temp);
            }
            htmlFile.close();
        }
        
    }

}

