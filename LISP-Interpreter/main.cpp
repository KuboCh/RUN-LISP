#include <cstdlib>
#include <iostream>
#include <string>
#include "Parser.h"

using namespace std;

// REPL = Read Eval Print Loop

int main(int argc, char** argv) {
    cout << "Welcome to LISP interpreter" << endl;
    int lineNo = 0;
    string line;
    Parser p(true); // True = talk!

    while (true) {
        cout << ++lineNo << ". > ";
        getline(cin, line);
        if (p.talkToMe)
            cout << "You said: " << line << endl;
        if (line == "bye" || line == "exit")
            break;
        p.parse(line);
    }
    cout << "Bye!";
    return 0;
}

