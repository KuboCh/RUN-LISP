#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

#ifndef PARSER2_H
#define PARSER2_H
class Array;
class Enviroment;

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

