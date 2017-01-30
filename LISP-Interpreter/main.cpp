#include <cstdlib>
#include <iostream>
#include <string>
#include "DataType.h"
#include "Environment.h"
#include "BuildInFunctions.h"
#include "Function.h"
#include "LispStack.h"
#include "Parser.h"
#include "Array.h"

using namespace std;

/*
 * Init Built-In functions
 */
void buildFunctions(Environment *e) {
    e->addFunction(new BuildInPlus());
    e->addFunction(new BuildInDefconst());
    e->addFunction(new BuildInDefvar());
    e->addFunction(new BuildInList());
    e->addFunction(new BuildInMinus());
    e->addFunction(new BuildInMultiplication());
    e->addFunction(new BuildInEqual());
}

int main(int argc, char** argv) {
    cout << "Welcome to LISP interpreter" << endl;
    int lineNo = 0;
    string line;
    Environment mainEnvironment;
    buildFunctions(&mainEnvironment);
    Function *mainFunction = new Function(&mainEnvironment);
    LispStack::getInstance().push(mainFunction);
    Parser parser;
    Array *parsedData;
    DataType * result;

    // REPL = Read Eval Print Loop
    while (true) { // Loop
        cout << ++lineNo << ". > ";
        getline(cin, line);
        if (line == "bye" || line == "exit")
            break;
        parsedData = parser.parse(line, mainEnvironment); // Read
        if (parsedData != NULL) {
            result = parsedData->eval(mainEnvironment); // Eval
            if (result != NULL) {
                cout << result->toString() << " (" << result->typeToString() << ")" << endl; // Print
            }
        }

        if (lineNo == 100) // proti zacykleniu
            break;
    }
    cout << "Bye!" << endl;
    return 0;
}
