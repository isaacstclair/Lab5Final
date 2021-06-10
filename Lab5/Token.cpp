#include "Token.h"
#include <string>
#include <iostream>

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    this->type = type;
    this->description = description;
    this->line = line;
}

std::string TokenTypeToString(TokenType type){

    switch(type){
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::ADD: return "ADD"; break;
        case TokenType::COMMA: return "COMMA"; break;
        case TokenType::LEFTPAREN: return "LEFT_PAREN"; break;
        case TokenType::MULTIPLY: return "MULTIPLY"; break;
        case TokenType::PERIOD: return "PERIOD"; break;
        case TokenType::QMARK: return "Q_MARK"; break;
        case TokenType::RIGHTPAREN: return "RIGHT_PAREN"; break;
        case TokenType::SCHEMES: return "SCHEMES"; break;
        case TokenType::FACTS: return "FACTS"; break;
        case TokenType::RULES: return "RULES"; break;
        case TokenType::QUERIES: return "QUERIES"; break;
        case TokenType::STRING: return "STRING"; break;
        case TokenType::COMMENT: return "COMMENT"; break;
        case TokenType::ID: return "ID"; break;
        case TokenType::EOF_TYPE: return "EOF"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
    }

    return "error";
}


void Token::ToString(){
    std::cout << "(" << TokenTypeToString(type) << "," << "\"" << description << "\"" << "," << line << ")" << std::endl;
}

std::string Token::GetStringError(){
    std::string error = "(" + TokenTypeToString(type) + "," + "\"" + description + "\"," + std::to_string(line) + ")";
    return(error);
}



TokenType Token::GetTokenType() {
    return(type);
}

std::string Token::GetTokenDescription(){
    return(description);
}
