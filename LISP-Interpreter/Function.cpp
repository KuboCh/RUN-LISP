#include "Function.h"
#include <string>
#include "Nil.h"

using namespace std;

Function::Function() {
    argCount = 0;
    functionEnviroment = new Enviroment();
}

Function::Function(Enviroment* e){
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
    //body.push_back(function);
}

DataType* Function::eval(Enviroment* e) {
    //TODO
    return new Nil();
}

bool Function::checkArgCount(int givenArgCount) {
    return givenArgCount == argCount;
}


