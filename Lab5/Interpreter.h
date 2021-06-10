
#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"


class Interpreter {

private:
    DatalogProgram datalog;
    Database database;
    std::vector<std::string> VectorSeenBefore;
    std::vector<int> VectorToProject;
public:
    Interpreter(DatalogProgram datalog, Database database);
    ~Interpreter();
    void Interpret();
    Relation EvaluatePredicate(const Predicate p);
    std::vector<Relation> EvaluatePredicates(std::vector<Predicate> p);
    bool CheckDuplicate(Parameter par);
    int GetFirstInstance(Parameter par);
    bool QueryCheck(std::vector<std::string> parameters);
    void EvaluateSchemes();
    void EvaluateFacts();
    void EvaluateRules();
    void EvaluateQueries();
    Relation SelectProjectRename(Relation relation);
};


#endif //INTERPRETER_H
