#ifndef EOFAUTOMATON_H
#define EOFAUTOMATON_H

#include "Automaton.h"

class EofAutomaton : public Automaton
{
public:
    EofAutomaton() : Automaton(TokenType::EOF_TYPE) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // EOFAUTOMATON_H

