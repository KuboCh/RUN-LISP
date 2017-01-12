#include "Function.h"
#include <string>
#include "Nil.h"

using namespace std;

Function::Function() {
}

Function::Function(const Function& orig) {
}

Function::~Function() {
}

int Function::getArgCount(){
    return argCount;
}

void Function::addParametr(string name) {
    args.push_back(Parametr(name, NULL, false));
    argCount++;
}

void Function::addToBody(Function* function) {
    body.push_back(function);
}

DataType* Function::eval(Enviroment* e) {
    //TODO
    return new Nil();
}


