#include <string>
#include <iostream>
#include "Number.h"
#include "String.h"
#include "False.h"
#include "Nil.h"
#include "True.h"
#include "Enviroment.h"

#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Parser {
public:
    Parser();
    Parser(bool talk);
    Parser(const Parser& orig);
    virtual ~Parser();
    DataType* parse(string line, Enviroment *e);
    
    DataType* readString(string line);
    DataType* readNumber(string line);
    DataType* readList(string line, Enviroment *e);
    DataType* readSymbol(string line, Enviroment *e);
    DataType* readParametr(bool constant, Enviroment *e);
    DataType* readFunction(Enviroment *e);
    DataType* callFunction(string functionName, Enviroment *e);
    bool talkToMe;
private:
};


#endif /* PARSER_H */

