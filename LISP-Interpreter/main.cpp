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
    string word;
    Enviroment mainEnviroment;
    buildFunctions(&mainEnviroment);
    Function *mainFunction = new Function(&mainEnviroment);
    LispStack::getInstance().push(mainFunction);

    //Parser p(true); // True = talk!
    Parser p(false); // True = talk!
    DataType * result;
    
    p.pushBack("(def inc4 (x) (inc3 (inc2 (inc1 0))))\n");
    p.pushBack("(def inc1 (x) (+ x 1))\n");
    p.pushBack("(def inc2 (x) (+ x 1))\n");
    p.pushBack("(def inc3 (x) (+ x 1))\n");
    
    
    // REPL = Read Eval Print Loop
    while (true) { // Loop
        cout << ++lineNo << ". > ";
        cin >> word; // Read
        if (p.talkToMe)
            cout << "Main: You said: " << word << endl;
        if (word == "bye" || word == "exit")
            break;
        result = p.parse(word, &mainEnviroment); // Eval + additional read
        result->print(); // Print
        cout << endl;
        //delete result; // Delete my garbage
        if (lineNo == 100) // proti zacykleniu
            break;
    }
    cout << "Bye!" << endl;
    return 0;
}
