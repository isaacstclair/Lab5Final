//
// Created by isaac on 5/20/2021.
//
#include <vector>
#include <string>
#include <sstream>
#include "Header.h"

#ifndef TUPLE_H
#define TUPLE_H


class Tuple {

private:
    std::vector<std::string> values;

public:
    Tuple(std::vector<std::string> values);
    ~Tuple();
    bool operator< (const Tuple & other) const;
    std::string TupleToString(int pos);
    std::string GetValue(int pos);
    bool SelectTuple(int pos, std::string match);
    int GetSize();
    void GetTupleString(std::vector<std::string> toPrint);

};


#endif //TUPLE_H
