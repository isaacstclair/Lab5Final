#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "AddAutomaton.h"
#include "CommentAutomaton.h"
#include "CommaAutomaton.h"
#include "FactsAutomaton.h"
#include "IDAutomaton.h"
#include "LeftParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "QMarkAutomaton.h"
#include "QueriesAutomaton.h"
#include "RightParenAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "StringAutomaton.h"
#include "UndefinedAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`

}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new UndefinedAutomaton());
    automata.push_back(new IDAutomaton());


}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata[0];


        //TODO: you need to handle whitespace in between tokens
        //Newlines

        while(isspace(input[0])){
            if (input[0] == '\n'){
                lineNumber += 1;
            }
            input.erase(0, 1);
            maxRead = 0;
        }

        //for each automaton in automata{}
        for(int i=0; i < static_cast<int>(automata.size()); i++){
            int inputRead = automata[i]->Start(input);
            if(inputRead > maxRead){
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNumber);
            lineNumber = lineNumber + maxAutomaton->NewLinesRead();
            if(newToken->GetTokenType() != TokenType::COMMENT){tokens.push_back(newToken);}
            //add newToken to collection of all tokens

        } else { //No machine accepted the input, so it is invalid
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0,maxRead), lineNumber);
            tokens.push_back(newToken);
            //add newToken to collection of all tokens
        }
        //remove maxRead characters from input
        input.erase(0, maxRead);

        while(isspace(input[0])){
            if (input[0] == '\n'){
                lineNumber += 1;
            }
            input.erase(0, 1);
            maxRead = 0;
        }

    }
    Token* newToken = new Token(TokenType::EOF_TYPE, input, lineNumber);
    tokens.push_back(newToken);
}

void Lexer::Print(){
    for(int i=0; i < static_cast<int>(tokens.size()); i++){
        tokens[i]->ToString();
    }
    std::cout << "Total Tokens = " << tokens.size();

}

std::vector<Token*> Lexer::getTokens(){
    return(tokens);
}