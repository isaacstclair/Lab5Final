#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <cctype>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    void Print();
    std::vector<Token*> getTokens();

};

#endif // LEXER_H

