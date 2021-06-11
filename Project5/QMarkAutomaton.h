#ifndef QMARKAUTOMATON_H
#define QMARKAUTOMATON_H

#include "Automaton.h"

class QMarkAutomaton : public Automaton
{
public:
    QMarkAutomaton() : Automaton(TokenType::QMARK) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // QMARKAUTOMATON_H