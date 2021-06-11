//
// Created by isaac on 5/20/2021.
//

#include <string>
#include <vector>
#include <set>
#include "Tuple.h"
#include "Header.h"
#include "Parameter.h"

#ifndef RELATION_H
#define RELATION_H


class Relation {

private:
    std::string name;
    Header header;
    std::set<Tuple> tuples;
    std::vector<std::pair<int,int>> matchedTuplesPairs;

public:
    Relation(std::string name, Header header);
    Relation(std::string name, Header header, std::set<Tuple> tuples);
    ~Relation();
    void AddTuple(Tuple newTuple);
    Relation Select(int index, std::string value);
    Relation Select(int index1, int index2);
    Relation Project(std::vector<int> columns);
    Relation Rename(std::vector<std::string> newName);
    Relation Join(Relation secondRelation);
    Header CombineHeaders(Header newHeader);
    std::string GetName();
    void RelationToString();
    int GetTupleSize();
    std::vector<std::string> GetParameters();
    Header GetHeader();
    std::vector<std::pair<int,int>> tuplesToMatch(Header newHeader);
    bool Joinable(Tuple tuple1, Tuple tuple2);
    Tuple JoinTuples(Tuple tuple1, Tuple tuple2);
    std::set<Tuple> GetTuples();
    bool SetCheck(Tuple tupleInsert);
    Relation ProjectSecond(std::vector<int> columns);
    void SetName(std::string name);
    void SetHeader(Header header);
};


#endif //RELATION_H
