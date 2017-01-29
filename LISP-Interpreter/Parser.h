#include <string>
#include <iostream>
#include <list>
#include <algorithm>    // std::reverse
#include <limits>
#include <stdlib.h>

using namespace std;

#ifndef PARSER_H
#define PARSER_H
class DataType;
class Enviroment;
class Function;
class Parametr;

class Parser {
public:
    Parser();
    Parser(bool talk);
    Parser(const Parser& orig);
    virtual ~Parser();
    DataType* parse(string line, Enviroment *e);
    void pushBack(string s);
    
    DataType* readString(string line);
    DataType* readNumber(string line);
    DataType* readList(string line, Enviroment *e);
    DataType* readSymbol(string line, Enviroment *e);
    DataType* readVariable(bool constant, Enviroment *e);
    DataType* readFunction(Enviroment *e);
    DataType* readFunctionCall(string functionName, Enviroment *e);
    list<Parametr*> readParametrsOfFunction(Enviroment *e, Function *function, int *varCount);
    pair<Function*, list<Parametr*> > readInBodyFunction(Enviroment* e, Function *function, int *varCount);
    bool talkToMe;
private:
};


#endif /* PARSER_H */

