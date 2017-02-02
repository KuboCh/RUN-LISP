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
#include "Memory.h"

using namespace std;

/*
 * Init Built-In functions
 */
void buildFunctions(Environment *e) {
    e->addFunction(new BuildInPlus());
    e->addFunction(new BuildInDefconst());
    e->addFunction(new BuildInDefvar());
    e->addFunction(new BuildInUndef());
    e->addFunction(new BuildInList());
    e->addFunction(new BuildInMinus());
    e->addFunction(new BuildInMultiplication());
    e->addFunction(new BuildInEqual());
    e->addFunction(new BuildInLower());
    e->addFunction(new BuildInGreater());
    e->addFunction(new BuildInAnd());
    e->addFunction(new BuildInOr());
    e->addFunction(new BuildInIf());
    e->addFunction(new BuildInFor());
    e->addFunction(new BuildInOut());
    e->addFunction(new BuildInReturn());
    e->addFunction(new BuildInAt());
    e->addFunction(new BuildInSet());
    e->addFunction(new BuildInDelete());
    e->addFunction(new BuildInAdd());
    e->addFunction(new BuildInLength());
}

int main(int argc, char** argv) {
    cout << "Welcome to LISP interpreter" << endl;
    int lineNo = 0;
    string line;
    Environment *mainEnvironment = Memory::getInstance().get();
    buildFunctions(mainEnvironment);
    Function *mainFunction = new Function(mainEnvironment);
    mainFunction->name = "main";
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
        parsedData = parser.parse(line); // Read
        if (parsedData != NULL) {
            result = parsedData->eval(mainEnvironment); // Eval
            if (result != NULL) {
                cout << result->toString() << " (" << result->typeToString() << ")" << endl; // Print
            }
        }
        // testing memory
        //        Environment *mainEnvironment2 = Memory::getInstance().get();
        //        Function *mainFunction2 = new Function(mainEnvironment2);
        //        mainFunction2->name = "main2";
        //        LispStack::getInstance().push(mainFunction2);

        if (lineNo == 100) // proti zacykleniu
            break;
    }
    cout << "Bye!" << endl;
    return 0;
}
