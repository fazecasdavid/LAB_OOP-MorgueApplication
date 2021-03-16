#include "utils.h"


std::vector<std::string> splitCommand(std::string line) {
    std::vector<std::string> splitLine;
    std::string token;
    if (line.find(" ") == std::string::npos) {
        splitLine.push_back(line);
        return splitLine;
    }
    token = line.substr(0, line.find(" "));
    splitLine.push_back(token);
    line.erase(0, line.find(" ") + 1);

    int position = 0;
    while ((position = line.find(", ")) != std::string::npos) {
        token = line.substr(0, position);
        splitLine.push_back(token);
        line.erase(0, position + 2);
    }
    splitLine.push_back(line);

    return splitLine;
}


std::vector<std::string> splitDelimiter(std::string line, std::string delimiter) {
    std::vector<std::string> splitLine;
    int position = 0;
    while ((position = line.find(delimiter)) != std::string::npos) {
        std::string token = line.substr(0, position);
        splitLine.push_back(token);
        line.erase(0, delimiter.length() + position);
    }
    splitLine.push_back(line);
    return splitLine;
}
