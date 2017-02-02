#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

#ifndef PARSER_H
#define PARSER_H
class Array;
class Environment;

class Parser {
public:
    Parser();
    Parser(const Parser& orig);
    virtual ~Parser();
    Array* parse(string line);
    int parenthesisCheck(string text);
    string getFullInput(string& line);
    list<string> tokenize(string input);
    static const bool PRINT = false;
private:
};

#endif /* PARSER_H */

