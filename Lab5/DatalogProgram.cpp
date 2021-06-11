#include "DatalogProgram.h"

void DatalogProgram::addScheme(Predicate scheme){SchemesPredicates.push_back(scheme);}

void DatalogProgram::addFact(Predicate fact){FactsPredicates.push_back(fact);}

void DatalogProgram::addQuery(Predicate query){QueriesPredicates.push_back(query);}

void DatalogProgram::addRule(Rule rule){Rules.push_back(rule);}

void DatalogProgram::addDomain(std::string domain){Domain.insert(domain);}

std::string DatalogProgram::DatalogProgramToString(){

    std::stringstream ss;

    for(int i=0; i<int(SchemesPredicates.size()); i++){
        if(i == 0){ss << SchemesPredicates.at(i).PredicateToString() << "\n";} else {
            ss << "  " << SchemesPredicates.at(i).PredicateToString() << "\n";
        }
    }

    std::string schemes = "Schemes(" + std::to_string(SchemesPredicates.size()) + "):\n  " + ss.str();

    ss.str(std::string());

    for(int i=0; i<int(FactsPredicates.size()); i++){
        if(i == 0){ss << FactsPredicates.at(i).PredicateToString() << ".\n";} else {
            ss << "  " << FactsPredicates.at(i).PredicateToString() << ".\n";
        }
    }

    std::string facts = "Facts(" + std::to_string(FactsPredicates.size()) + "):\n  " + ss.str();

    ss.str(std::string());

    for(int i=0; i<int(Rules.size()); i++){
        if(i == 0){ss << Rules.at(i).RuleToString() << ".\n";} else {
            ss << "  " << Rules.at(i).RuleToString() << ".\n";
        }
    }

    std::string rules = "Rules(" + std::to_string(Rules.size()) + "):\n  " + ss.str();

    ss.str(std::string());

    for(int i=0; i<int(QueriesPredicates.size()); i++){
        if(i == 0){ss << QueriesPredicates.at(i).PredicateToString() << "?\n";} else {
            ss << "  " << QueriesPredicates.at(i).PredicateToString() << "?\n";
        }
    }

    std::string queries = "Queries(" + std::to_string(QueriesPredicates.size()) + "):\n  " + ss.str();

    ss.str(std::string());

    for(auto it = Domain.begin(); it != Domain.end(); ++it){
        ss << "  " << *it << std::endl;
    }

    std::string domain = "Domain(" + std::to_string(Domain.size()) + "):\n" + ss.str();



    std::string datalogString = schemes + facts + rules + queries + domain;

    return datalogString;
}