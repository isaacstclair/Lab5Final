

#include "Parameter.h"

Parameter::Parameter(std::string parameter){
    this->parameter = parameter;
}

Parameter::~Parameter(){}

std::string Parameter::GetParameter(){
    return parameter;
}

