#include "Predicate.h"
#include <string>
#include <vector>
#include <sstream>

#ifndef RULE_H
#define RULE_H

class Rule {

private:
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;

public:
    Rule();
    ~Rule();
    std::string RuleToString();
    void setHead(Predicate head);
    void addBody(Predicate body);
    std::string RulesToString(std::vector<Predicate> body);
    Predicate GetHeadPredicates();
    std::vector<Predicate> GetBodyPredicates();
    std::vector<std::string> GetBodyNames();

};


#endif // RULE_H
