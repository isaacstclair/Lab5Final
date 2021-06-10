#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum class TokenType {
    COLON, COLON_DASH, ADD, COMMA, LEFTPAREN, MULTIPLY, PERIOD, QMARK, RIGHTPAREN, SCHEMES, FACTS, RULES, QUERIES,
    STRING, COMMENT, ID, EOF_TYPE, UNDEFINED
};

std::string TokenTypeToString(TokenType val);

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType type;
    std::string description;
    int line;


public:
    Token(TokenType type, std::string description, int line);
    void ToString();
    std::string GetStringError();
    TokenType GetTokenType();
    std::string GetTokenDescription();

    // TODO: add other needed methods
};

#endif // TOKEN_H

