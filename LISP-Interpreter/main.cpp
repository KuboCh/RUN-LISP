#include <cstdlib>
#include <iostream>
#include <string>
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {
    cout << "Welcome to LISP interpreter" << endl;
    int lineNo = 0;
    string line;
    string word;
    Parser p(true); // True = talk!
    //    Parser p(false); // True = talk!
    DataType * result;

    // REPL = Read Eval Print Loop
    while (true) {
        cout << ++lineNo << ". > ";
        //        getline(cin, line);
        cin >> word;
        if (p.talkToMe)
            cout << "Main: You said: " << word << endl;
        if (word == "bye" || word == "exit")
            break;
        result = p.parse(word);
        result->print();
        //delete result; // Delete my garbage
    }
    cout << "Bye!" << endl;
    return 0;
}

