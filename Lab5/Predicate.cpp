
#include <iostream>
#include "Predicate.h"

Predicate::Predicate(){}

Predicate::Predicate(std::string name, std::vector<Parameter> parameters){
    this->name = name;
    this->parameters = parameters;
}


Predicate::~Predicate(){}

std::string Predicate::PredicateToString(){
    std::stringstream ss;
    if(parameters.size() != 0) {
        for (int i = 0; i < int(parameters.size()) - 1; i++) {
              ss << parameters.at(i).GetParameter() << ",";
        }
        ss << parameters.at(parameters.size()-1).GetParameter();
    }

    std::string predicate = name + "(" + ss.str() + ")";
    return predicate;
}

std::string Predicate::QueryToString(){
    std::string query = PredicateToString() + '?';
    return query;
}

std::string Predicate::GetName(){
    return this->name;
}

std::vector<std::string> Predicate::GetParameters(){
    std::vector<std::string> stringParameters;
    for(int i=0; i < int(parameters.size()); i++){
        stringParameters.push_back(parameters.at(i).GetParameter());
    }

    return stringParameters;
}


