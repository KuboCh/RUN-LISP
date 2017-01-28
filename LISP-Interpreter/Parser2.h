#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "String.h"
#include "Number.h"
#include "Variable.h"
#include "DataType.h"
#include "Enviroment.h"
#include "True.h"
#include "False.h"
#include "Nil.h"
#include "Error.h"
#include "Array.h"
#include "Symbol.h"

using namespace std;

#ifndef PARSER2_H
#define PARSER2_H

class Parser2 {
public:
    Parser2();
    Parser2(const Parser2& orig);
    virtual ~Parser2();
    Array* parse(string line, Enviroment& e);
    int parenthesisCheck(string text);
    string getFullInput(string& line);
    list<string> tokenize(string input);
private:
};

#endif /* PARSER2_H */

