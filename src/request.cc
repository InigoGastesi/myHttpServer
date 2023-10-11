#include <request.hh>

std::vector<std::string> splitSpaces(std::string str)
{
    char separator = ' ';
    int startIndex = 0, endIndex = 0;
    std::vector<std::string> strings;
    for (int i = 0; i <= str.size(); i++)
    {
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size())
        {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            temp.erase(remove(temp.begin(), temp.end(), ':'), temp.end()); //remove A from string
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

namespace http
{
    Request::Request(std::string request) : m_rawRequest(request)
    {
        parseRequest();
    }
    Request::~Request()
    {
    }

    void Request::parseRequest()
    {
        std::vector<std::string> lines;
        std::string tempHeader = m_rawRequest.substr(0, m_rawRequest.find("\r\n\r\n") + 4);
        m_body = m_rawRequest.substr(m_rawRequest.find("\r\n\r\n") + 4, std::string::npos);

        size_t index = 0;
        while ((index = tempHeader.find("\n")) != std::string::npos)
        {
            lines.push_back(tempHeader.substr(0, index - 1));
            tempHeader = tempHeader.substr(index + 1);
        }

        std::vector<std::string> spaces;
        for (std::string line : lines)
        {
            std::vector<std::string> spaceSplit = splitSpaces(line);
            spaces.insert(spaces.end(), spaceSplit.begin(), spaceSplit.end());
        }
        m_header.insert(std::pair<std::string, std::string>("method", spaces[0]));
        m_header.insert(std::pair<std::string, std::string>("URI", spaces[1]));
        addToHeader("Content-Length", spaces);
        m_contentLength = stoi(m_header["Content-Length"]);
        // m_header.insert(std::pair<std::string, std::string>("URI", spaces[1]));
    }

    void Request::addToHeader(std::string key, const std::vector<std::string> &spaces)
    {
        auto it = std::find(spaces.begin(), spaces.end(), key);
        if (it != spaces.end())
        {
            int index = it - spaces.begin();
            m_header.insert(std::pair<std::string, std::string>(key, spaces[index + 1]));
        }
    }

    unsigned int Request::getContentLength()
    {
        return m_contentLength;
    }
}