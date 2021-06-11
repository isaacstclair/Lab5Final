
#include <vector>
#include <string>
#include "Parameter.h"
#include <sstream>

#ifndef PREDICATE_H
#define PREDICATE_H


class Predicate {
private:
    std::string name;
    std::vector<Parameter> parameters;

public:
    Predicate();
    Predicate(std::string name, std::vector<Parameter> parameters);
    ~Predicate();
    std::string PredicateToString();
    std::string QueryToString();
    std::string GetName();
    std::vector<std::string> GetParameters();

};


#endif // PREDICATE_H
