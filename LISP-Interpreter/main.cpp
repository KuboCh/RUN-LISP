#include <cstdlib>
#include <iostream>
#include <string>
#include "Parser.h"
#include "BuildInFunctions.h"
#include "LispStack.h"

using namespace std;

void buildFunctions(Enviroment *e) {
    e->addFunction(new BuildInPlus());
    e->addFunction(new BuildInDefconst());
    e->addFunction(new BuildInDefvar());
    e->addFunction(new BuildInList());
    e->addFunction(new BuildInMinus());
    e->addFunction(new BuildInMultiplication());
}

int main(int argc, char** argv) {
    cout << "Welcome to LISP interpreter" << endl;
    int lineNo = 0;
    string line;
    string word;
    Enviroment mainEnviroment;
    buildFunctions(&mainEnviroment);
    Function *mainFunction = new Function();
    mainFunction->functionEnviroment = &mainEnviroment;
    LispStack::getInstance().push(mainFunction);
    //Parser p(true); // True = talk!
    Parser p(false); // True = talk!
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
        result = p.parse(word, &mainEnviroment);
        result->print();
        cout << endl;
        //delete result; // Delete my garbage
    }
    cout << "Bye!" << endl;
    return 0;
}
