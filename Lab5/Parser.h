#pragma once

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>
#include <list>
#include "Predicate.h"

class Parser
{
private:
    int counter = 0;
    int Advance();
    std::vector<Token*> tokens;
    std::vector<Parameter> stringVector;
    std::vector<Parameter> idVector;
    std::vector<Parameter> parameterVector;
    std::vector<Predicate> predicateVector;

public:
    Parser(std::vector<Token*> tokens);
    ~Parser();
    void ParseDatalogProgram();
    bool Match(TokenType toMatch);

    //Terminals
    void ParseTerminal(TokenType type);

    //Non-Terminals
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    Predicate headPredicate();
    Predicate predicate();
    std::vector<Predicate> predicateList();
    std::vector<Parameter> parameterList();
    std::vector<Parameter> stringList();
    std::vector<Parameter> idList();
    Parameter parameter();
    std::string ToString();

    DatalogProgram datalog;

};

