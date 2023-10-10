#include <httpParser.hh>

std::vector<std::string> split(std::string str, char separator){
    int startIndex = 0, endIndex = 0;
    std::vector<std::string> strings;
    std::string header = str.substr(0, str.find("\r\n\r\n"));
    std::cout << header << std::endl;
    for (int i = 0; i <= str.size(); i++) {
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}


namespace http{
    httpParser::httpParser(std::string httpRequest){
        std::vector<std::string> splitedHeader = split(httpRequest, ' ');
        // for(auto row : splitedHeader)
        //     std::cout << row << std::endl;
    }
    httpParser::~httpParser(){

    }
}