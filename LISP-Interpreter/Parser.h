#include <string>
#include <iostream>

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
    void readString(string line, int from);
    void readNumber(string line);
    void readList(string line);
    void readSymbol(string line);
    bool talkToMe;
private:
};


#endif /* PARSER_H */

