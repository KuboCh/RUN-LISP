#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// REPL = Read Eval Print Loop

int main(int argc, char** argv) {
    cout << "Welcome to LISP interpreter" << endl;
    int lineNo = 0;
    string line;

    while(true) {
        cout << ++lineNo << ". > ";
        getline(cin, line);
        cout << "You said: " << line << endl;
        if(line == "bye" || line == "exit") 
            break;
    }
    cout << "Bye!";
    return 0;
}

