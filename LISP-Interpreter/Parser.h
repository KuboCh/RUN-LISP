#include <string>
#include <iostream>
#include "Number.h"
#include "String.h"
#include "False.h"
#include "Nil.h"
#include "True.h"

#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Parser {
public:
    Parser();
    Parser(bool talk);
    Parser(const Parser& orig);
    virtual ~Parser();
    void parse(string line);
    
    String readString(string line);
    Number readNumber(string line);
    void readList(string line);
    DataType* readSymbol(string line);
    bool talkToMe;
private:
};


#endif /* PARSER_H */

