#include "Parser.h"

using namespace std;

Parser::Parser() {
    talkToMe = false;
}

Parser::Parser(bool talk) {
    talkToMe = talk;
}

Parser::~Parser() {
}

string readString(string line, int from) {
    cout << "You should learn me to read strings." << endl;
    int p = line.find('"', 1);
    if (p == -1) {

    }
    line = line.substr(1);
}

void readList(string line) {
    cout << "You should learn me to read lists." << endl;
}

void readNumber(string line) {
    cout << "You should learn me to read numbers." << endl;
}

void readSymbol(string line) {
    cout << "You should learn me to read symbols." << endl;
}

/*
 * Parse content of the line as:
 * 1. Atom (Number, String, etc.)
 * 2. Symbol -> could be evaluated as atom/another symbol/list
 * 3. List -> functions/atoms/symbols/...
 */
void Parser::parse(string line) {
    switch (line[0]) {
        case '"':
            if (talkToMe)
                cout << "Parser: Hmm... It could be a string!" << endl;
            //            readString(line, 0);
            break;
        case '(':
            if (talkToMe)
                cout << "Parser: Hmm... It could be a list!" << endl;
            //            readList(line);
            break;
        default:
            if (line[0] >= '0' && line[0] <= '9') {
                if (talkToMe)
                    cout << "Parser: Hmm... It could be a number!" << endl;
                //                readNumber(line);
            } else {
                if (talkToMe)
                    cout << "Parser: Hmm... It could be a symbol!" << endl;
                //            readSymbol(line);
            }
            break;
    }
}


