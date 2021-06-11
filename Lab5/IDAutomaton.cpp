#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    if (isalnum(input[index])) {
        inputRead++;
        index++;
        S1(input);
    } else if (!isalnum(input[index])){
        return;
    }
    else {
        Serr();
    }
}