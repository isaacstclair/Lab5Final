
#include "Header.h"


Header::Header(std::vector<std::string> attributes){
    this->attributes = attributes;
}

Header::Header(){}

Header::~Header(){
    attributes.clear();
}

void Header::ChangeHeader(std::vector<std::string> newAttributes){
    this->attributes = newAttributes;
}

std::string Header::GetAttribute(int pos){
    return(this->attributes.at(pos));
}

int Header::Size(){
    return int(this->attributes.size());
}

