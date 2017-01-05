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

void parse(string line) {
    switch (line[0]) {
        case '"':
            readString(line, 0);
            break;
        case '(':
            
            break;
        default:
            if (line[0] >= '0' && line[0] <= '9'){
                //number
            }
            //premenna
            break;
    }
}


