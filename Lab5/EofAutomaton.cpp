#include "EofAutomaton.h"

void EofAutomaton::S0(const std::string& input) {
    if (input[index] == EOF) {
        inputRead = 1;
    }
    else {
        Serr();
    }
}