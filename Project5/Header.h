//
// Created by isaac on 5/20/2021.
//

#include <vector>
#include <string>

#ifndef HEADER_H
#define HEADER_H


class Header {

private:
    std::vector<std::string> attributes;
public:
    Header(std::vector<std::string> attributes);
    Header();
    ~Header();
    void ChangeHeader(std::vector<std::string> newAttributes);
    std::string GetAttribute(int pos);
    int Size();
};


#endif //HEADER_H
