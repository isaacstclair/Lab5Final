//
// Created by isaac on 5/20/2021.
//

#include <iostream>
#include "Relation.h"

Relation::Relation(std::string name, Header header){
    this->name = name;
    this->header = header;
}

Relation::Relation(std::string name, Header header, std::set<Tuple> tuples){
    this->name = name;
    this->header = header;
    this->tuples = tuples;
}

Relation::~Relation(){
    tuples.clear();
    matchedTuplesPairs.clear();
}

void Relation::AddTuple(Tuple newTuple){
    tuples.insert(newTuple);
}

Relation Relation::Select(int index, std::string value){
    //TODO return a tuple with only the string value
    std::set<Tuple> matchedTuples;
    for(Tuple t : tuples){
        if(t.SelectTuple(index, value)){
            matchedTuples.insert(t);
        }
    }

    Relation newRelation = Relation(this->name, this->header, matchedTuples);
    return newRelation;
}

Relation Relation::Select(int index1, int index2){
    std::set<Tuple> matchedTuples;
    for(Tuple t : tuples){
        if(t.GetValue(index1) == t.GetValue(index2)){matchedTuples.insert(t);}
    }

    Relation newRelation = Relation(this->name, this->header, matchedTuples);
    return newRelation;
}

Relation Relation::Project(std::vector<int> columns){
    std::set<Tuple> matchedTuples;
    std::vector<std::string> tupleVect;

    for(Tuple t : tuples){
        for(int i=0; i < int(columns.size()); i++) {
            std::string value = t.GetValue(columns.at(i));
            tupleVect.push_back(value);
        }
        Tuple newTuple = Tuple(tupleVect);
        matchedTuples.insert(newTuple);
        tupleVect.clear();
    }

    Relation newRelation = Relation(this->name, this->header, matchedTuples);
    return newRelation;
}

Relation Relation::Rename(std::vector<std::string> newName){
    Relation newRelation = Relation(this->name, this->header, this->tuples);
    newRelation.header.ChangeHeader(newName);
    return newRelation;
}

void Relation::RelationToString(){

    for(Tuple t : tuples){
        std::cout << "  ";
        for(int i=0; i < this->header.Size(); i++){

            if(i < this->header.Size()-1) {
                std::cout << this->header.GetAttribute(i) << "=" << t.TupleToString(i) << ", ";
            } else{
                std::cout << this->header.GetAttribute(i) << "=" << t.TupleToString(i) << std::endl;
            }
        }
    }
}

std::string Relation::GetName(){
    return this->name;
}

int Relation::GetTupleSize(){
    return int(tuples.size());
}

std::vector<std::string> Relation::GetParameters(){
    std::vector<std::string> parameters;
    for(int i=0; i<int(header.Size()); i++){
        parameters.insert(parameters.end(),header.GetAttribute(i));
    }
    return(parameters);
}

Relation Relation::Join(Relation secondRelation){

    std::vector<std::string> matchedParameters;
    std::set<Tuple> newTuples;
    matchedTuplesPairs.clear();

    std::string newName = "NewRelation";
    Header newHeader = CombineHeaders(secondRelation.GetHeader());
    matchedTuplesPairs = tuplesToMatch(secondRelation.GetHeader());

    if(int(matchedTuplesPairs.size()) == 0 && (!tuples.empty() | secondRelation.tuples.empty())){
        for (Tuple j : tuples) {
            for(Tuple k : secondRelation.GetTuples()) {
                if(Joinable(j,k)) {
                    newTuples.insert(JoinTuples(j, k));
                }
            }
        }
    } else if(int(matchedTuplesPairs.size()) > 0 && (!tuples.empty() | secondRelation.tuples.empty())) {
        for (int i = 0; i < int(matchedTuplesPairs.size()); i++) {
            for (Tuple j : this->tuples) {
                for(Tuple k : secondRelation.GetTuples()) {
                    if(Joinable(j,k)) {
                        newTuples.insert(JoinTuples(j, k));
                    }
                }
            }
        }
    }

    Relation newRelation("NewRelation", newHeader, newTuples);
    matchedTuplesPairs.clear();
    return newRelation;

}

Header Relation::CombineHeaders(Header newHeader){
    std::vector<std::string> combinedHeader;

    for(int i=0; i<int(this->header.Size()); i++){
        combinedHeader.push_back(this->header.GetAttribute(i));
    }


    for(int i=0; i<int(newHeader.Size()); i++){
        int sum=0;
        for(int j=0; j<int(this->header.Size()); j++){
            if(newHeader.GetAttribute(i) == header.GetAttribute(j)){
                sum++;
            }
        }
        if(sum == 0) {
            combinedHeader.push_back(newHeader.GetAttribute(i));
        }
    }
    Header returnHeader = Header(combinedHeader);
    return returnHeader;
}

Header Relation::GetHeader(){
    return header;
}

std::vector<std::pair<int,int>> Relation::tuplesToMatch(Header newHeader){
    std::vector<std::pair<int,int>> tupleCol;

    for(int i=0; i<int(newHeader.Size()); i++){
        for(int j=0; j<int(this->header.Size()); j++){
            if(this->header.GetAttribute(j) == newHeader.GetAttribute(i)){
                tupleCol.push_back(std::pair<int, int>(j,i));
            }
        }
    }

    return tupleCol;
}

bool Relation::Joinable(Tuple tuple1, Tuple tuple2){
    int sum = 0;
    if(int(matchedTuplesPairs.size()) == 0){
        return true;
    }
    for(int i=0; i<int(matchedTuplesPairs.size()); i++){
        if(tuple1.GetValue(matchedTuplesPairs.at(i).first) == tuple2.GetValue(matchedTuplesPairs.at(i).second)){
                sum++;
        }
    }
    if(sum == int(matchedTuplesPairs.size())){
        return true;
    }
    return false;
}

Tuple Relation::JoinTuples(Tuple tuple1, Tuple tuple2){
    std::vector<std::string> newTuple;

    if(int(matchedTuplesPairs.size()) == 0){
        for(int i=0; i<tuple1.GetSize(); i++){
            newTuple.push_back(tuple1.GetValue(i));
        }
        for(int i=0; i<tuple2.GetSize(); i++){
            newTuple.push_back(tuple2.GetValue(i));
        }
        return newTuple;
    } else {

        for (int i = 0; i < tuple1.GetSize(); i++) {
            newTuple.push_back(tuple1.GetValue(i));
        }


        for (int i = 0; i < tuple2.GetSize(); i++) {
            int indicator = 0;
            for (int j = 0; j < int(matchedTuplesPairs.size()); j++) {
                if (i == matchedTuplesPairs.at(j).second) {
                    indicator++;
                }
            }
            if(indicator == 0){
                newTuple.push_back(tuple2.GetValue(i));
            }
        }

        Tuple tuple = Tuple(newTuple);
        return (tuple);
    }
}

std::set<Tuple> Relation::GetTuples(){
    return this->tuples;
}

bool Relation::SetCheck(Tuple tupleInsert){

    if(tuples.find(tupleInsert) != tuples.end()){
        return true;
    } else{
        return false;
    }
}

Relation Relation::ProjectSecond(std::vector<int> columns){
    std::set<Tuple> matchedTuples;
    std::vector<std::string> tupleVect;
    std::vector<std::string> newHeader;

    for(int i=0; i<int(columns.size()); i++){
        newHeader.push_back(this->header.GetAttribute(columns.at(i)));
    }
    Header head = Header(newHeader);

    for(Tuple t : tuples){
        for(int i=0; i < int(columns.size()); i++) {
            std::string value = t.GetValue(columns.at(i));
            tupleVect.push_back(value);
        }
        Tuple newTuple = Tuple(tupleVect);
        matchedTuples.insert(newTuple);
        tupleVect.clear();
    }

    Relation newRelation = Relation(this->name, head, matchedTuples);
    return newRelation;
}

void Relation::SetName(std::string name){
    this->name = name;
}

void Relation::SetHeader(Header header){
    this->header = header;
}