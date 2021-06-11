
#include "Rule.h"

Rule::Rule(){}

Rule::~Rule(){}

std::string Rule::RuleToString(){
    std::string rule = "rule";
    rule = headPredicate.Predicate::PredicateToString() + " :- " + RulesToString(bodyPredicates);
    return rule;
}

void Rule::setHead(Predicate head){
    headPredicate = head;
}

void Rule::addBody(Predicate body){
    bodyPredicates.push_back(body);
}

std::string Rule::RulesToString(std::vector<Predicate> body){
    std::stringstream ss;
    for (int i=0; i < int(body.size()); i++){
        if(i == int(body.size())-1){ss << body.at(i).PredicateToString();}else{ss << body.at(i).PredicateToString() << ",";}
    }

    std::string ruleVector = ss.str();
    return(ruleVector);
}

Predicate Rule::GetHeadPredicates(){
    return this->headPredicate;
}


std::vector<Predicate> Rule::GetBodyPredicates(){
    return this->bodyPredicates;
}

std::vector<std::string> Rule::GetBodyNames(){
    std::vector<std::string> BodyNames;
    for(int i=0; i<int(bodyPredicates.size()); i++){
        BodyNames.push_back(bodyPredicates.at(i).GetName());
    }
    return(BodyNames);
}

