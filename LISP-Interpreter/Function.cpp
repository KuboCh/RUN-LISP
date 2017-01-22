#include "Function.h"
#include <string>
#include "Nil.h"

using namespace std;

Function::Function() {
    argCount = 0;
    functionEnviroment = new Enviroment();
}

Function::Function(Enviroment* e) {
    functionEnviroment = e;
    argCount = 0;
}

Function::Function(const Function& orig) {
}

Function::~Function() {
}

void Function::addArgument(string name) {
    //args.push_back(Parametr(name, NULL, false));
    argsNames.push_back(name);
    argCount++;
}

void Function::addToBody(Function* function, list<Parametr*> parametrs) {
    body.push_back(pair<Function*, list<Parametr*> >(function, parametrs));
}

DataType* Function::eval(Enviroment* e) {
    for (list<pair<Function*, list<Parametr*> > >::iterator it = body.begin(); it != body.end(); ++it) {
        if(it != --body.end()){
            (*it).first->eval(e);
        } else { // the last evaluated value is result value (Ruby-like)
            return (*it).first->eval(e);
        }
    }
    return new Nil();
}

bool Function::checkArgCount(int givenArgCount) {
    return givenArgCount == argCount;
}


