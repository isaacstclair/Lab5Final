
#include "Parser.h"


Parser::Parser(std::vector<Token*> tokens){
    this->tokens = tokens;
    ParseDatalogProgram();
}

Parser::~Parser(){
    //clean up memory
}

bool Parser::Match(TokenType toMatch){
    if(tokens.at(counter)->GetTokenType() == toMatch){
        return true;
    } else{return false;}
}

void Parser::ParseDatalogProgram() {
    ParseTerminal(TokenType::SCHEMES);
    ParseTerminal(TokenType::COLON);
    scheme();
    schemeList();
    ParseTerminal(TokenType::FACTS);
    ParseTerminal(TokenType::COLON);
    factList();
    ParseTerminal(TokenType::RULES);
    ParseTerminal(TokenType::COLON);
    ruleList();
    ParseTerminal(TokenType::QUERIES);
    ParseTerminal(TokenType::COLON);
    query();
    queryList();
    ParseTerminal(TokenType::EOF_TYPE);

}


//TERMINALS
void Parser::ParseTerminal(TokenType type){
    if(Match(type)){
        Advance();
    } else{
        std::string error = tokens.at(counter)->GetStringError();
        throw(error);
    }
}


//NONTERMINALS
void Parser::schemeList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::ID) {
        scheme();
        schemeList();
    }
}
void Parser::factList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::ID) {
        fact();
        factList();
    }
}
void Parser::ruleList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::ID) {
        rule();
        ruleList();
    }
}
void Parser::queryList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::ID) {
        query();
        queryList();
    }
}
void Parser::scheme(){
    std::string name = tokens.at(counter)->GetTokenDescription();
    ParseTerminal(TokenType::ID);
    ParseTerminal(TokenType::LEFTPAREN);
    Parameter first = tokens.at(counter)->GetTokenDescription();
    ParseTerminal(TokenType::ID);
    std::vector<Parameter> parameters = idList();
    idVector.clear();
    parameters.insert(parameters.begin(),first);
    ParseTerminal(TokenType::RIGHTPAREN);
    Predicate predicate = Predicate(name, parameters);
    //push back onto the scheme vector
    datalog.addScheme(predicate);
}

void Parser::fact(){
    std::string name = tokens.at(counter)->GetTokenDescription();
    ParseTerminal(TokenType::ID);
    ParseTerminal(TokenType::LEFTPAREN);
    Parameter first = tokens.at(counter)->GetTokenDescription();
    std::string domain = tokens.at(counter)->GetTokenDescription();
    ParseTerminal(TokenType::STRING);
    std::vector<Parameter> parameters = stringList();
    stringVector.clear();
    parameters.insert(parameters.begin(), first);
    ParseTerminal(TokenType::RIGHTPAREN);
    Predicate predicate = Predicate(name, parameters);
    ParseTerminal(TokenType::PERIOD);
    datalog.addFact(predicate);

    for(int i=0; i < int(parameters.size()); i++){
        datalog.addDomain(parameters.at(i).GetParameter());
    }

}
void Parser::rule(){
    parameterVector.clear();
    predicateVector.clear();
    stringVector.clear();
    idVector.clear();
    Predicate head = headPredicate();
    ParseTerminal(TokenType::COLON_DASH);
    Predicate firstBody = predicate();
    std::vector<Predicate> body = predicateList();
    body.insert(body.begin(), firstBody);
    ParseTerminal(TokenType::PERIOD);
    Rule rule = Rule();
    rule.setHead(head);
    for(int i=0; i < int(body.size()); i++) {
        rule.addBody(body.at(i));
    }
    datalog.addRule(rule);
}
void Parser::query(){
    parameterVector.clear();
    Predicate queryPredicate = predicate();
    ParseTerminal(TokenType::QMARK);
    datalog.addQuery(queryPredicate);

}
Predicate Parser::headPredicate(){
    std::string name = tokens.at(counter)->GetTokenDescription();
    ParseTerminal(TokenType::ID);
    ParseTerminal(TokenType::LEFTPAREN);
    Parameter first = tokens.at(counter)->GetTokenDescription();
    ParseTerminal(TokenType::ID);
    std::vector<Parameter> parameters = idList();
    parameters.insert(parameters.begin(), first);
    ParseTerminal(TokenType::RIGHTPAREN);
    Predicate predicate = Predicate(name, parameters);
    idVector.clear();
    return(predicate);
}
Predicate Parser::predicate(){
    idVector.clear();
    parameterVector.clear();
    stringVector.clear();
    std::string name = tokens.at(counter)->GetTokenDescription();
    ParseTerminal(TokenType::ID);
    ParseTerminal(TokenType::LEFTPAREN);
    Parameter first = parameter();
    std::vector<Parameter> body = parameterList();
    body.insert(body.begin(), first);
    ParseTerminal(TokenType::RIGHTPAREN);
    Predicate predicate = Predicate(name, body);
    return(predicate);
}
std::vector<Predicate> Parser::predicateList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::COMMA) {
        ParseTerminal(TokenType::COMMA);
        Predicate next = predicate();
        predicateVector.push_back(next);
        predicateList();
        return(predicateVector);
    } else {
        return(predicateVector);
    }
}
std::vector<Parameter> Parser::parameterList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::COMMA) {
        ParseTerminal(TokenType::COMMA);
        parameterVector.push_back(tokens.at(counter)->GetTokenDescription());
        parameter();
        parameterList();
        return(parameterVector);
    } else{
        return(parameterVector);
    }
}
std::vector<Parameter> Parser::stringList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::COMMA) {
        ParseTerminal(TokenType::COMMA);
        stringVector.push_back(tokens.at(counter)->GetTokenDescription());
        ParseTerminal(TokenType::STRING);
        stringList();
        return(stringVector);
    } else{
        return(stringVector);
    }
}
std::vector<Parameter> Parser::idList(){
    if(tokens.at(counter)->GetTokenType() == TokenType::COMMA) {
        ParseTerminal(TokenType::COMMA);
        idVector.push_back(tokens.at(counter)->GetTokenDescription());
        ParseTerminal(TokenType::ID);
        idList();
        return(idVector);
    } else{
        return(idVector);
    }
}
Parameter Parser::parameter(){
    if(Match(TokenType::STRING)){
        Parameter parameter = tokens.at(counter)->GetTokenDescription();
        ParseTerminal(TokenType::STRING);
        return(parameter);
    } else if (Match(TokenType::ID)){
        Parameter parameter = tokens.at(counter) -> GetTokenDescription();
        ParseTerminal(TokenType::ID);
        return(parameter);
    } else {
        Parameter parameter  = tokens.at(counter)->GetTokenDescription();
        return(parameter);
    }

}

int Parser::Advance(){
    counter = counter+1;
    return(counter);
}


std::string Parser::ToString() {
    std::string datalogString = datalog.DatalogProgramToString();
    return(datalogString);
}