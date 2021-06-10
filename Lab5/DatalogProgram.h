
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H


class DatalogProgram {

public:
    std::vector<Predicate> SchemesPredicates;
    void addScheme(Predicate scheme);
    std::vector<Predicate> FactsPredicates;
    void addFact(Predicate fact);
    std::vector<Predicate> QueriesPredicates;
    void addQuery(Predicate Query);
    std::vector<Rule> Rules;
    void addRule(Rule rule);
    std::set<std::string> Domain;
    void addDomain(std::string domain);
    std::string DatalogProgramToString();
};


#endif // DATALOGPROGRAM_H
