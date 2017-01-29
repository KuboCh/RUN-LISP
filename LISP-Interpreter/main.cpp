#include <cstdlib>
#include <iostream>
#include <string>
#include "DataType.h"
#include "Enviroment.h"
#include "BuildInFunctions.h"
#include "Function.h"
#include "LispStack.h"
#include "Parser2.h"
#include "Evaluator.h"
#include "Array.h"

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
    Enviroment mainEnviroment;
    buildFunctions(&mainEnviroment);
    Function *mainFunction = new Function(&mainEnviroment);
    LispStack::getInstance().push(mainFunction);
    Parser2 parser;
    Array *parsedData;
    Evaluator evaluator;
    DataType * result;

    // REPL = Read Eval Print Loop
    while (true) { // Loop
        cout << ++lineNo << ". > ";
        getline(cin, line);
        if (line == "bye" || line == "exit")
            break;
        parsedData = parser.parse(line, mainEnviroment); // Read
        //        if ((*parsedData).isAtom()) {
        //            cout << (*parsedData).toString() << endl;
        //        } else {
        //            cout << "[";
        //            for (int i = 0; i < (*parsedData).a.size(); i++) {
        //                cout << ((*parsedData).a[i])->toString();
        //                if (i + 1 != (*parsedData).a.size())
        //                    cout << ",";
        //            }
        //            cout << "]";
        //        }
        //        cout << endl;
        if (parsedData != NULL) {
            result = evaluator.eval(parsedData, mainEnviroment);
            if (result != NULL) {
                cout << result->toString() << endl;
            }
        }

        if (lineNo == 100) // proti zacykleniu
            break;
    }
    cout << "Bye!" << endl;
    return 0;
}
