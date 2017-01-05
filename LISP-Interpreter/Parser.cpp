#include "Parser.h"

using namespace std;

Parser::Parser() {}

Parser::~Parser() {}

string readString(string line, int from) {
    int p = line.find('"', 1);
    if (p == -1) {
        
    }
    line = line.substr(1);  
}

void readList(string line){}
void readNumber(string line){}

/*
 * Parse content of the line as:
 * 1. Atom (Number, String, etc.)
 * 2. Symbol -> could be evaluated as atom/another symbol/list
 * 3. List -> functions/atoms/symbols/...
 */
void parse(string line) {
    switch (line[0]) {
        case '"':
            readString(line, 0);
            break;
        case '(':
            readList(line);
            break;
        default:
            if (line[0] >= '0' && line[0] <= '9'){
                readNumber(line);
            }
            //premenna
            break;
    }
}


